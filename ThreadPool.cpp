//
// Created by yuval on 26/01/17.
//

#include <iostream>
#include <zconf.h>
#include "ThreadPool.h"

using namespace std;

extern "C"

void* start_thread(void* arg)
{
    ThreadPool* tp = (ThreadPool*) arg;
    tp->execute_thread();
    return NULL;
}



ThreadPool::ThreadPool(int pool_size) {

    this->m_pool_size = pool_size;

    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void*) this);
        if (ret != 0) { /* error handling */ }
        m_threads.push_back(tid);
    }
    cout << m_pool_size << " threads created by the thread pool" << endl;
}


ThreadPool::~ThreadPool() {

    for (int i = 0; i < m_pool_size; i++) {
        cout << "need care about delete" << endl;
        pthread_join(m_threads[i], NULL);
    }
    cout << m_pool_size << " threads exited from the thread pool" << endl;
}

void *ThreadPool::execute_thread() {
    Task* task = NULL;
    while(true) {
        while (m_tasks.empty()){ sleep(1); }
        task = m_tasks.front();
        m_tasks.pop_front();
        (*task)();
    }
    return NULL;
}

int ThreadPool::add_task(Task *task) {
    m_tasks.push_back(task);
}



