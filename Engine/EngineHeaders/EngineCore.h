#pragma once

/*! \mainpage My Personal Index Page
*
* \section intro_sec Introduction
*
* The purpose of this engine is to provide a set of classes in a loosely coupled way
* designed to support common game development requirements.
*
* \subsection This engine is designed to support:
* Basic game loop management <br>
* Multi and single monitor rendering <br>
* Physics <br>
* Asset loadng <br>
* Constructive solid geometry <br>
*
*/

/// Function pointer to the draw or update functions you would like EngineCore to call each tick.
typedef void(*GameLoopCallback)(double);

/// Core class, initialises services in correct order and provides game loop.
class EngineCore
{
public:
	EngineCore();
	~EngineCore();
	EngineCore(EngineCore const&) = delete;
	void operator=(EngineCore const&) = delete;

private:
	bool gameloopPaused = false;
	bool gameloopShouldStop = false;

public:
	/// Allocates and initialises resources.
	/** 
		Needs to be called first.
		\return 0 if initialised successfully
	*/
	int Initialize();

	/// Releases resources.
	void ShutDown();

	/// Sets the root path that file names are relative to.
	/**
	This file path will be appended to the begining of file names used in asset loading.
	\param rootPath The file path to use as the root path.
	*/
	void SetAssetRootPath(const char* rootPath);

	/// Begins game loop.
	/*!
	An optional fixed timestep game loop.
	Provide RunGameLoop() with the functions you would like it to call each tick and RunGameLoop() will call them at the appropriate times.
	\param UpdateCallback The GameLoopCallback to your update function.
	\param RenderCallback The GameLoopCallback to your render function.
	*/
	int RunGameLoop(GameLoopCallback UpdateCallback, GameLoopCallback RenderCallback);
	
	/// Pauses the game loop.
	void PauseGameLoop(){ gameloopPaused = true; };
	
	/// Continues the game loop.
	void ResumeGameLoop(){ gameloopPaused = false; };
	
	/// Exits the game loop.
	void TerminateGameLoop(){ gameloopShouldStop = true; };
};

