#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>

#include "GpuJobManager.h"
#include "WindowManager.h"
#include "InputService.h"
#include "ContentService.h"
#include "SceneManager.h"
#include "PhysicsService.h"

Game* Game::Instance = 0;

Game::Game(std::shared_ptr<sf::RenderWindow> window)
{
	Instance = this;
	ptr_JobManager = std::unique_ptr<GpuJobManager>(new GpuJobManager());
	ptr_WindowManager = std::unique_ptr<WindowManager>(new WindowManager(window));
	ptr_InputService = std::unique_ptr<InputService>(new InputService(window));
	ptr_ContentService = std::unique_ptr<ContentService>(new ContentService());
	ptr_SceneManager = std::unique_ptr<SceneManager>(new SceneManager());
	ptr_PhysicsService = std::unique_ptr<PhysicsService>(new PhysicsService());
}

Game::~Game()
{

}

void Game::Update(double DeltaT)
{
	ptr_SceneManager->UpdateActiveScene(DeltaT);
	ptr_PhysicsService->Update(DeltaT);
}

void Game::Draw(double DeltaT)
{
	// wait for current gpu job if any to finish - if a reasonable time budget was set this should have no effect.
	ptr_JobManager->PauseProcessing();
	// draw the scene.
	ptr_SceneManager->DrawActiveScene(DeltaT);
	// allow job manager to resume processing jobs.
	ptr_JobManager->BeginProcessing(15);
}

