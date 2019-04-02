#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}

void SceneManager::SetActiveScene(std::shared_ptr<Scene> newScene)
{
	ptr_ActiveScene = newScene;
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	if (auto ActiveScene = ptr_ActiveScene.lock())
	{
		return ActiveScene;
	}
	else
	{
		return nullptr;
	}
}

void SceneManager::DrawActiveScene(double DeltaTime)
{
	if (auto ActiveScene = ptr_ActiveScene.lock())
	{
		ActiveScene->Draw(DeltaTime);
	}
}

void SceneManager::UpdateActiveScene(double DeltaTime)
{
	if (auto ActiveScene = ptr_ActiveScene.lock())
	{
		ActiveScene->Update(DeltaTime);
	}
}
