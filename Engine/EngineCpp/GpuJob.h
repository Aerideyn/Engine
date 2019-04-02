#pragma once

class GpuJob
{
private:
	virtual void Complete() = 0;
public:
	virtual bool RunStep() = 0;
	virtual ~GpuJob() = 0;
};

inline GpuJob::~GpuJob(){};
