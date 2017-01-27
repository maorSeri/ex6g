//
// Created by yuval on 26/01/17.
//
#include "Task.h"

Task::Task(void (*fn_ptr)(void *), void *arg) {
    this->m_fn_ptr = fn_ptr;
    this->m_arg = arg;
    // TODO Auto-generated constructor stub
}

Task::~Task() {
    // TODO Auto-generated destructor stub
}

void Task::operator()() {
    (*m_fn_ptr)(m_arg);

}
