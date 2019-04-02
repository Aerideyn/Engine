#pragma once
#include <deque>
#include <memory>
#include <thread>
#include <condition_variable>

class PhysicsMesh;

class PhysicsMeshProcessingQue
{
	friend class PhysicsService;
private:
	PhysicsMeshProcessingQue();

	// if the thread should terminate; set when the game is about to close.
	bool ThreadShouldTerminate = false;

	std::deque<std::weak_ptr<PhysicsMesh>> jobQue;

	std::thread jobThread;
	std::mutex QueMutex;
	std::condition_variable QueCheck;

	void ProcessJobs();

public:
	void SubmitJob(std::weak_ptr<PhysicsMesh> mesh);
	~PhysicsMeshProcessingQue();
};

