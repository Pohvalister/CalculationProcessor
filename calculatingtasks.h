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
    CalculatingTask(TVal& value, ConcurrentStack<QString>* st, TVal (*oper)(TVal, TVal), TVal (*conv)(QString))
        : QObject(NULL)
        , dataholder(st)
        , operation(oper)
        , conversion(conv)
        , output_value(value)
        , have_work(true)
    {}

    ~CalculatingTask()
    {}

    void run(){
        while(have_work){
            bool stack_not_empty;
            have_work = !stop_flag;
            QString new_values = dataholder->pop(stack_not_empty);
            have_work = stack_not_empty || have_work;

            if (stack_not_empty){

                QStringList line_array = new_values.split(" ");

                for (const QString & str : qAsConst(line_array)){
                    TVal new_value = conversion(str);
                    output_value = operation(output_value, new_value);

                }
            }

        }
    };


public:
    static bool stop_flag;

    static void restoreFlag(){
        stop_flag = false;
    }

    static void onReadingFinished(){
        stop_flag = true;
    }

private:
    ConcurrentStack<QString>* dataholder;

    std::function<TVal(TVal, TVal)> operation;
    std::function<TVal(QString)> conversion;
    TVal& output_value;

    bool have_work;
};

template<typename TVal>
bool CalculatingTask<TVal>::stop_flag = false;


#endif // CALCULATINGTASKS_H
