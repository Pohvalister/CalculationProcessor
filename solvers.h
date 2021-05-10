#ifndef DATASOLVERS_H
#define DATASOLVERS_H

#include <QtCore/QThreadPool>

#include <iostream>


static const int THREAD_COUNT = 3;

//class to calculate values from given data
class Solver : public QObject
{
    Q_OBJECT

public:

    virtual int maxThreads(){return _max_threads;}
    virtual void setMaxThreads(int num){_max_threads = num;}

    virtual QString solve(QString filename) = 0;

    //virtual void print_solve(QString filename) {std::cout<<solve(filename);}


protected:
    int _max_threads;
};

//Class to use int types for data evaluation
class IntegerSolver : public Solver{
    QString solve(QString filename);
};

//Class to use long long int types for data evaluation
class LongLongSolver : public Solver{
    QString solve(QString filename);
};


#endif // DATASOLVERS_H
