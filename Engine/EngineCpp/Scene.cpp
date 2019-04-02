#include "Scene.h"
#include "Camera.h"


Scene::Scene()
{
	ptr_camera = std::shared_ptr<Camera>(new Camera());
}

Scene::~Scene()
{

}

Camera& Scene::GetActiveCamera()
{
	return *ptr_camera;
}


