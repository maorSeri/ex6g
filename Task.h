//
// Created by yuval on 26/01/17.
//

#ifndef EX6_TASK_H
#define EX6_TASK_H

class Task {
private:
    void (*m_fn_ptr)(void*);
    void* m_arg;

public:
    Task(void (*fn_ptr)(void*), void* arg);
    ~Task();
    void operator()(); // functor

};

#endif //EX6_TASK_H
