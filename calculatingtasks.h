#ifndef CALCULATINGTASKS_H
#define CALCULATINGTASKS_H
#include <iostream>

#include <QObject>
#include <QRunnable>

#include "concurrentlist.h"

template<typename TVal>
class CalculatingTask : public QObject, public QRunnable
{

public:
    CalculatingTask(ConcurrentStack<TVal>* st, TVal (*func)(TVal, TVal))
        : QObject(NULL)
        , dataholder(st)
        , operation(func)
        , output_value(0)
        , have_work(true)
    {}

    void run(){
        while(have_work){
            std::cout<<"stop_flag"<<stop_flag<<' ';
            bool stack_not_empty;
            have_work = !stop_flag;
            int new_value = dataholder->pop(stack_not_empty);
            have_work|=stack_not_empty;
            if (stack_not_empty){
                output_value = operation(output_value, new_value);
                std::cout<<new_value<<' ';
            }
        }
    };

    TVal get_value(){return output_value;};

public:
    static bool stop_flag;

    static void onReadingFinished(){
        stop_flag = true;
    }

private:
    ConcurrentStack<TVal>* dataholder;

    std::function<TVal(TVal, TVal)> operation;
    TVal output_value;

    bool have_work;
};

template<typename TVal>
bool CalculatingTask<TVal>::stop_flag = false;


#endif // CALCULATINGTASKS_H
