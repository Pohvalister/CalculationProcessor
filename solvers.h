#ifndef DATASOLVERS_H
#define DATASOLVERS_H

#include <QtCore/QThreadPool>

static const int THREAD_COUNT = 3;

//class to calculate values from given data
class Solver : public QObject
{
    Q_OBJECT

public:

    virtual int maxThreads(){return _max_threads;}
    virtual void setMaxThreads(int num){_max_threads = num;}

    virtual void solve(QString filename) = 0;

protected:
    int _max_threads;
};

//Class to use int types for data evaluation
class IntegerSolver : public Solver{
    void solve(QString filename);
};

//Class to use long long int types for data evaluation
class LongLongSolver : public Solver{
    void solve(QString filename);
};


#endif // DATASOLVERS_H
