#include "solvers.h"

#include "filereadingtask.h"
#include "calculatingtasks.h"
#include "concurrentlist.h"


/*void IntegerSolver::solve(QString filename){
    QThreadPool::globalInstance()->setMaxThreadCount(_max_threads);

    ConcurrentStack<int>* XOR_stack = new ConcurrentStack<int>();
    ConcurrentStack<int>* ADD_stack = new ConcurrentStack<int>();
    CalculatingTask<int>* XOR_task = new CalculatingTask<int>(XOR_stack, [](int a, int b){return a^b;});
    CalculatingTask<int>* ADD_task1 = new CalculatingTask<int>(ADD_stack, [](int a, int b){return a+b;});
    CalculatingTask<int>* ADD_task2 = new CalculatingTask<int>(ADD_stack, [](int a, int b){return a+b;});

    QVector<ConcurrentStack<int>*> stack_vector;
    stack_vector.push_back(XOR_stack);
    stack_vector.push_back(ADD_stack);
    FileReadingTask *fr_task = new FileReadingTask(filename, stack_vector);

    connect(fr_task, &FileReadingTask::readingFinished, &CalculatingTask<int>::onReadingFinished);//connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));//Q_OBJECT is not compatible with templates


    QThreadPool::globalInstance()->start(fr_task);
    QThreadPool::globalInstance()->start(ADD_task1);
    QThreadPool::globalInstance()->start(ADD_task2);
    QThreadPool::globalInstance()->start(XOR_task);

    QThreadPool::globalInstance()->waitForDone();


    std::cout<<XOR_task->get_value()<<' ';
    std::cout<<ADD_task1->get_value() + ADD_task2->get_value();


    return;
}*/

void LongLongSolver::solve(QString filename){
    QThreadPool::globalInstance()->setMaxThreadCount(_max_threads);

    ConcurrentStack<long long int>* XOR_stack = new ConcurrentStack<long long int>();
    ConcurrentStack<long long int>* ADD_stack = new ConcurrentStack<long long int>();
    CalculatingTask<long long int>* XOR_task = new CalculatingTask<long long int>(XOR_stack, [](long long int a, long long int b){return a^b;});
    CalculatingTask<long long int>* ADD_task1 = new CalculatingTask<long long int>(ADD_stack, [](long long int a, long long int b){return a+b;});
    CalculatingTask<long long int>* ADD_task2 = new CalculatingTask<long long int>(ADD_stack, [](long long int a, long long int b){return a+b;});

    QVector<ConcurrentStack<long long int>*> stack_vector;
    stack_vector.push_back(XOR_stack);
    stack_vector.push_back(ADD_stack);
    FileReadingTask *fr_task = new FileReadingTask(filename, stack_vector);

    connect(fr_task, &FileReadingTask::readingFinished, &CalculatingTask<long long int>::onReadingFinished);//connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));//Q_OBJECT is not compatible with templates


    QThreadPool::globalInstance()->start(fr_task);
    QThreadPool::globalInstance()->start(ADD_task1);
    QThreadPool::globalInstance()->start(ADD_task2);
    QThreadPool::globalInstance()->start(XOR_task);

    QThreadPool::globalInstance()->waitForDone();


    std::cout<<XOR_task->get_value()<<' ';
    std::cout<<ADD_task1->get_value() + ADD_task2->get_value();

    return;
}
