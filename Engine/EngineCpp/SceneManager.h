#pragma once
#include <memory>

class Scene;

class SceneManager
{
	friend class Game;
private:
	std::weak_ptr<Scene> ptr_ActiveScene;
	SceneManager();

	void UpdateActiveScene(double DeltaTime);
	void DrawActiveScene(double DeltaTime);
public:

	void SetActiveScene(std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> GetActiveScene();

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;
	~SceneManager();
};

