#include "PhysicsMeshProcessingQue.h"
#include "PhysicsMesh.h"
#include <iostream>
PhysicsMeshProcessingQue::PhysicsMeshProcessingQue()
{
	jobQue = std::deque<std::weak_ptr<PhysicsMesh>>();
	jobThread = std::thread(&PhysicsMeshProcessingQue::ProcessJobs, this);
}

PhysicsMeshProcessingQue::~PhysicsMeshProcessingQue()
{
	// order thread to halt if it has not already.
	ThreadShouldTerminate = true;

	// break it out of it's sleep.
	QueCheck.notify_all();

	// wait until thread ends.
	if (jobThread.joinable())
	{
		jobThread.join();
	}
}

void PhysicsMeshProcessingQue::SubmitJob(std::weak_ptr<PhysicsMesh> mesh)
{
	jobQue.push_back(mesh);
	if (jobQue.size() > 0) QueCheck.notify_all();
}

void PhysicsMeshProcessingQue::ProcessJobs()
{
	while (!ThreadShouldTerminate)
	{
		// pause the thread until thread is permitted to resume.
		std::unique_lock<std::mutex> lock = std::unique_lock<std::mutex>(QueMutex);
		QueCheck.wait(lock);

		// begin processing of the jobs while jobs are available and the thread is allowed to continue doing so.
		while (jobQue.size() > 0 && !ThreadShouldTerminate)
		{
			std::cout << "Jobs in physics mesh que: " << jobQue.size() << std::endl;
			// if the mesh still exists, register it. 
			if (auto job = jobQue.front().lock()) job->RegisterMesh(); 

			// in either case remove the mesh from the job que.
			jobQue.pop_front();
		}
	}
}