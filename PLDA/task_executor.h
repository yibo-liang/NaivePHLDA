#pragma once

#ifndef TASK_EXECUTOR
#define TASK_EXECUTOR
#include "shared_header.h"
#include "job_config.h"
#include "sync_data.h"
#include "task.h"
#include "model.h"

class TaskExecutor
{
public:
	
	JobConfig config;

	int MODE = P_MPI;
	int procNumber;
	bool isMaster = false;

	

	void receiveMasterTasks(vector<Task> tasks, Model model); // master node task executor should use this, so no mpi is used for faster speed
	void receiveRemoteTasks(); //all other proecess should use this

	void execute();

	TaskExecutor( JobConfig config);
	~TaskExecutor();

private:
	
	vector<Task> tasks;
	Model model; //model for this topic model task, only available on Master node executor. Generated & initialised from job.

	SynchronisationData sampleTask(Task &task); //since each task is only subset of the corpus, we need to return all data in the model that need to be synchronized.
	void runMaster();
	void runSlave();

};

#endif // !TASK_EXECUTOR