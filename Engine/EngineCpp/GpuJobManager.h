#pragma once
#include <deque>
#include <memory>
#include <thread>
#include <condition_variable>

#include "GpuJob.h"

namespace Planetoid
{
	class QuadTreeNode;
}

class GpuJobManager
{
	friend class Game;
private:
	// if the thread should terminate; set when the game is about to close.
	bool ThreadShouldTerminate = false;

	// If the thread should pause to free up the gpu for drawing.
	bool ThreadShouldPause = true;

	// Alloted job processing time remaining. Thread will pause when exhausted.
	int remainingTime = 0;

	std::thread jobThread;

	std::mutex QueMutex;
	std::condition_variable QueCheck;

	std::deque<std::unique_ptr<GpuJob>> jobQue;

	// will create a thread only if there is no active thread.
	void StartThreadIfNotRunning();

	// begin processing the job que.
	void ProcessJobs();


	GpuJobManager(GpuJobManager const&);
	void operator=(GpuJobManager const&);
	GpuJobManager();

public:

	// Intended to be called when game is about to draw, will pause the thread once the current job finishes
	// Then will sleep until either setTimeBudget is called or if the job list is empty - SubmitJob
	void PauseProcessing();

	// submits a job into processing que. Que is FIFO.
	void SubmitJob(std::unique_ptr<GpuJob> Job);

	// sets the maximum time the que may continue to process new jobs for and will begin the processing if not already began. Will once budget has expired. 
	void BeginProcessing(int budget);

	
	~GpuJobManager();
};
