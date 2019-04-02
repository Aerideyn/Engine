#pragma once
#include <memory>
class Camera;

class Scene
{
	friend class SceneManager;

private:	
	virtual void Update(double DeltaT) = 0;
	virtual void Draw(double DeltaT) = 0;

protected:
	std::shared_ptr<Camera> ptr_camera;

public:
	Scene();
	Camera& GetActiveCamera();
	Scene(Scene const&) = delete;
	void operator=(Scene const&) = delete;
	virtual ~Scene();
};

