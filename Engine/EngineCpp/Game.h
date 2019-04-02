#pragma once
#include <memory>

namespace sf { class RenderWindow; }

class GpuJobManager;
class WindowManager;
class InputService;
class ContentService;
class SceneManager;
class PhysicsService;

/*============= Game =====================
*	
*
*
*/

class Game
{	
	friend class EngineCore;

private:

	static Game* Instance;

	std::unique_ptr<GpuJobManager> ptr_JobManager;
	std::unique_ptr<WindowManager> ptr_WindowManager;
	std::unique_ptr<InputService> ptr_InputService;
	std::unique_ptr<ContentService> ptr_ContentService;
	std::unique_ptr<SceneManager> ptr_SceneManager;
	std::unique_ptr<PhysicsService> ptr_PhysicsService;
	
	// hide copy constructors - don't implement.
	Game(Game const&); 
	void operator=(Game const&);

	// private constructor - called by friend "application"
	Game(std::shared_ptr<sf::RenderWindow> window);

	// called by application, Will update the scene.
	void Update(double DeltaT);

	// called by application, Will draw the scene.
	void Draw(double DeltaT);

public:
	~Game();
	inline static GpuJobManager& GetJobManager(){ return *Instance->ptr_JobManager; };
	inline static WindowManager& GetWindowManager(){ return *Instance->ptr_WindowManager; };
	inline static InputService& GetInputService(){ return *Instance->ptr_InputService; };
	inline static ContentService& GetContentService(){ return *Instance->ptr_ContentService; };
	inline static SceneManager& GetSceneManager(){ return *Instance->ptr_SceneManager; };
	inline static PhysicsService& GetPhysicsService(){ return *Instance->ptr_PhysicsService; };
};

