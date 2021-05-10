#ifndef CALCULATINGTASKS_H
#define CALCULATINGTASKS_H

#include <QObject>
#include <QRunnable>

#include "concurrentlist.h"

template<typename TVal>
class CalculatingTask : public QObject, public QRunnable
{
public:
    CalculatingTask(ConcurrentStack<TVal>* st, TVal (*func)(TVal, TVal))
        : dataholder(st)
        , operation(func)
        , output_value(0)
        , stop_flag(false), have_work(true)
    {}

    void run(){
        while(!stop_flag || have_work){
            int new_value = dataholder->pop(have_work);
            output_value = operation(output_value, new_value);
        }
    };

    TVal get_value(){return output_value;};

private slots:
    void onReadingFinished(int){stop_flag = true;}

private:
    ConcurrentStack<TVal>* dataholder;

    std::function<TVal(TVal, TVal)> operation;
    TVal output_value;
    bool stop_flag, have_work;
};


#endif // CALCULATINGTASKS_H
