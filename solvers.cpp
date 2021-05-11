#include <QTextStream>

#include "solvers.h"

#include "filereadingtask.h"
#include "calculatingtasks.h"
#include "concurrentstack.h"

long long int LongLongSolver::convert(QString str){
    return str.toLongLong();
}

QString LongLongSolver::solve(QString filename){
    QFile data_file(filename);
    if (!data_file.open(QIODevice::ReadOnly)){
        return "";
    }

    QThreadPool::globalInstance()->setMaxThreadCount(MAX_THREAD_COUNT);

    //answer_values initalization
    ll ADD_value = 0, SUB_value, XOR_value = 0;
    QTextStream file_stream(&data_file);
    file_stream>>SUB_value;
    data_file.close();


    ConcurrentStack<QString> XOR_stack;
    ConcurrentStack<QString> ADD_stack;

    if (!data_file.open(QIODevice::ReadOnly)){
        return "";
    }
    CalculatingTask<ll>* XOR_task = new CalculatingTask<ll>(XOR_value, &XOR_stack, [](const ll a, const ll b){return a^b;}, convert);
    CalculatingTask<ll>* ADD_task = new CalculatingTask<ll>(ADD_value, &ADD_stack, [](const ll a, const ll b){return a+b;}, convert);

    QVector<ConcurrentStack<QString>*> stack_vector;
    stack_vector.push_back(&XOR_stack);
    stack_vector.push_back(&ADD_stack);


    FileReadingTask* fr_task = new FileReadingTask (&data_file, stack_vector);

    connect(fr_task, &FileReadingTask::readingFinished, &CalculatingTask<ll>::onReadingFinished);//connect(fr_task, SIGNAL(readingFinished(int)), ADD_task, SLOT(onReadingFinished(int)));//Q_OBJECT is not compatible with templates


    QThreadPool::globalInstance()->start(fr_task);
    QThreadPool::globalInstance()->start(ADD_task);
    QThreadPool::globalInstance()->start(XOR_task);


    QThreadPool::globalInstance()->waitForDone();

    CalculatingTask<ll>::restoreFlag();


    return QString::number(ADD_value) + ' ' + QString::number(SUB_value + SUB_value - ADD_value) + ' ' + QString::number(XOR_value);
}
