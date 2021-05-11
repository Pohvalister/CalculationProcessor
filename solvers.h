#ifndef DATASOLVERS_H
#define DATASOLVERS_H

#include <QtCore/QThreadPool>


static const int MAX_THREAD_COUNT = 3;

//class to calculate values from given data
class Solver : public QObject
{
    Q_OBJECT

public:


    virtual QString solve(QString filename) = 0;


};


//Class to use long long int types for data evaluation
class LongLongSolver : public Solver{
    QString solve(QString filename);

private:
    typedef long long int ll;
    static ll convert(QString str);
};


#endif // DATASOLVERS_H
