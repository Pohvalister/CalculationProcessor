#include "solvers.h"

#include "filereadingtask.h"
#include "calculatingtasks.h"
#include "concurrentlist.h"


QString LongLongSolver::solve(QString filename){
    typedef long long int ll;
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_THREAD_COUNT + 1);

    ConcurrentStack<ll> XOR_stack = ConcurrentStack<ll>();
    ConcurrentStack<ll> ADD_stack = ConcurrentStack<ll>();
    ll XOR_val=0, ADD_val1=0, ADD_val2=0;

    CalculatingTask<ll>* XOR_task = new CalculatingTask<ll>(XOR_val, &XOR_stack, [](ll a, ll b){return a^b;});
    CalculatingTask<ll>* ADD_task1 = new CalculatingTask<ll>(ADD_val1, &ADD_stack, [](ll a, ll b){return a+b;});
    CalculatingTask<ll>* ADD_task2 = new CalculatingTask<ll>(ADD_val2, &ADD_stack, [](ll a, ll b){return a+b;});

    QVector<ConcurrentStack<ll>*> stack_vector;
    stack_vector.push_back(&XOR_stack);
    stack_vector.push_back(&ADD_stack);
    FileReadingTask* fr_task = new FileReadingTask (filename, stack_vector);

    connect(fr_task, &FileReadingTask::readingFinished, &CalculatingTask<ll>::onReadingFinished);//connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));//Q_OBJECT is not compatible with templates


    QThreadPool::globalInstance()->start(fr_task);
    QThreadPool::globalInstance()->start(ADD_task1);
    QThreadPool::globalInstance()->start(ADD_task2);
    QThreadPool::globalInstance()->start(XOR_task);


    QThreadPool::globalInstance()->waitForDone();


    QString answer = QString::number(ADD_val1 + ADD_val2);
    answer += (" " + QString::number(XOR_val));

    return answer;
}
