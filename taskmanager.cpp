#include <iostream>

#include "taskmanager.h"
#include "filereadingtask.h"
#include "calculatingtasks.h"
#include "concurrentlist.h"


void TaskManager::start(QString filename){
    QThreadPool *pool = new QThreadPool(this);
    pool->setMaxThreadCount(_max_threads);

    ConcurrentStack<int>* XOR_stack = new ConcurrentStack<int>;
    ConcurrentStack<int>* ADD_stack = new ConcurrentStack<int>;
    CalculatingTask<int>* XOR_task = new CalculatingTask<int>(XOR_stack, [](int a, int b){return a^b;});
    CalculatingTask<int>* ADD_task = new CalculatingTask<int>(ADD_stack, [](int a, int b){return a+b;});

    QVector<ConcurrentStack<int>*> stack_vector;
    stack_vector.push_back(XOR_stack);
    stack_vector.push_back(ADD_stack);
    FileReadingTask* fr_task = new FileReadingTask(filename, stack_vector);

    connect(fr_task, SIGNAL(readingFinished(int)), XOR_task, SLOT(onReadingFinished(int)));
    connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));

    pool->start(XOR_task);
    pool->start(ADD_task);

    pool->start(fr_task);

    pool->waitForDone();

    std::cout<<XOR_task->get_value();
    std::cout<<ADD_task->get_value();

    return;
}
