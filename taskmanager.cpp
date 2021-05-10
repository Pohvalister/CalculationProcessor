#include <iostream>

#include "taskmanager.h"
#include "filereadingtask.h"
#include "calculatingtasks.h"
#include "concurrentlist.h"

TaskManager::TaskManager(){}

void TaskManager::start(QString filename){
    QThreadPool::globalInstance()->setMaxThreadCount(_max_threads);
    //QThreadPool *pool = new QThreadPool(this);
    //pool->setMaxThreadCount(_max_threads);

    ConcurrentStack<int>* XOR_stack = new ConcurrentStack<int>;
    ConcurrentStack<int>* ADD_stack = new ConcurrentStack<int>;
    CalculatingTask<int> XOR_task(XOR_stack, [](int a, int b){return a^b;});
    CalculatingTask<int> ADD_task(ADD_stack, [](int a, int b){return a+b;});

    QVector<ConcurrentStack<int>*> stack_vector;
    stack_vector.push_back(XOR_stack);
    stack_vector.push_back(ADD_stack);
    FileReadingTask fr_task(filename, stack_vector);

    connect(&fr_task, &FileReadingTask::readingFinished, &XOR_task, &CalculatingTask<int>::slot_onReadingFinished);
    connect(&fr_task, &FileReadingTask::readingFinished, &XOR_task, &CalculatingTask<int>::slot_onReadingFinished);
    //connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));//Q_OBJECT is not compatible with templates

    /*pool->start(&fr_task);
    pool->start(&XOR_task);
    pool->start(&ADD_task);



    pool->waitForDone();
*/
    QThreadPool::globalInstance()->start(&fr_task);


    std::cout<<XOR_task.get_value();
    std::cout<<ADD_task.get_value();

    return;
}
