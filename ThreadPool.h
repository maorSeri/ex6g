//
// Created by yuval on 26/01/17.
//

#ifndef EX6_THREADPOOL_H
#define EX6_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <vector>
#include <pthread.h>


class ThreadPool
{
private:
    bool stop;
    int m_pool_size;
    std::vector<pthread_t> m_threads;
    std::deque<Task*> m_tasks;
    pthread_mutex_t lock;

    /*
    queue<Job *> jobs_queue;
	int threads_num;
	pthread_t* threads;
	bool stop;
	pthread_mutex_t lock;
     */

public:
    ThreadPool(int pool_size);
    ~ThreadPool();
    void* execute_thread();
    int add_task(Task* task);
    void terminate();
};

#endif //EX6_THREADPOOL_H
