#include "GpuJobManager.h"

// TODO: In run, remaining time is not yet being subtracted after each step.

GpuJobManager::GpuJobManager()
{
	jobQue = std::deque<std::unique_ptr<GpuJob>>();
	jobThread = std::thread(&GpuJobManager::ProcessJobs, this);
}

GpuJobManager::~GpuJobManager()
{
	// order thread to halt if it has not already.
	ThreadShouldTerminate = true;

	// break it out of it's sleep.
	ThreadShouldPause = false;
	QueCheck.notify_all();

	// wait until thread ends.
	if (jobThread.joinable())
	{
		jobThread.join();
	}
}


void GpuJobManager::ProcessJobs()
{
	while (!ThreadShouldTerminate)
	{
		// pause the thread until thread is permitted to resume.
		std::unique_lock<std::mutex> lock = std::unique_lock<std::mutex>(QueMutex);
		QueCheck.wait(lock, [&](){return !ThreadShouldPause; });

		// begin processing of the jobs while there is time left, jobs available and the thread is allowed to continue doing so.
		while (remainingTime > 0 && jobQue.size() > 0 && !ThreadShouldPause)
		{ 
			if (jobQue.front()->RunStep()) jobQue.pop_front();
			remainingTime -= 15;
		}
	}
}

void GpuJobManager::StartThreadIfNotRunning()
{
	if (ThreadShouldPause && jobQue.size() > 0)
	{
		ThreadShouldPause = false;
		QueCheck.notify_all();
	}
}

void GpuJobManager::SubmitJob(std::unique_ptr<GpuJob> job)
{
	// que is now solely responsible for the job.
	jobQue.push_back(std::move(job));
	StartThreadIfNotRunning();
}

void GpuJobManager::BeginProcessing(int budget)
{
	remainingTime = budget;	
	StartThreadIfNotRunning();
}

void GpuJobManager::PauseProcessing()
{
	ThreadShouldPause = true;
}