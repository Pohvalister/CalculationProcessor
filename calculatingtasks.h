#ifndef CALCULATINGTASKS_H
#define CALCULATINGTASKS_H

#include <QObject>
#include <QRunnable>

#include "concurrentlist.h"

//Runnable class to apply commutative function to items in <st>
template<typename TVal>
class CalculatingTask : public QObject, public QRunnable
{

public:
    CalculatingTask(TVal& value, ConcurrentStack<TVal>* st, TVal (*func)(TVal, TVal))
        : QObject(NULL)
        , dataholder(st)
        , operation(func)
        , output_value(value)
        , have_work(true)
    {}

    ~CalculatingTask()
    {}

    void run(){
        while(have_work){
            bool stack_not_empty;
            have_work = !stop_flag;
            TVal new_value = dataholder->pop(stack_not_empty);
            have_work|=stack_not_empty;

            if (stack_not_empty)
                output_value = operation(output_value, new_value);

        }
    };

    //TVal get_value(){return output_value;};

public:
    static bool stop_flag;

    static void onReadingFinished(){
        stop_flag = true;
    }

private:
    ConcurrentStack<TVal>* dataholder;

    std::function<TVal(TVal, TVal)> operation;
    TVal& output_value;

    bool have_work;
};

template<typename TVal>
bool CalculatingTask<TVal>::stop_flag = false;


#endif // CALCULATINGTASKS_H
