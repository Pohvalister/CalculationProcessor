#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QtCore/QThreadPool>

static const int THREAD_COUNT = 3;

class TaskManager : public QObject
{
    Q_OBJECT

public:
    TaskManager();

    int maxThreads(){return _max_threads;}
    void setMaxThreads(int num){_max_threads = num;}

    void start(QString filename);

private:
    int _max_threads;

};

#endif // TASKMANAGER_H
