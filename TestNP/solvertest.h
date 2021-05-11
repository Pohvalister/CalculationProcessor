#ifndef SOLVERTEST_H
#define SOLVERTEST_H

#include <QObject>
#include <QTest>

#include <iostream>

#include "../solvers.h"
#include "basic_solver.h"

template<typename Func, typename... Args>
void benchmark(int iterCount, Func func, Args... args){

    QVector<int> elapsedTimes;
    for (int i = 0; i < iterCount; i++){
        QElapsedTimer time;
        time.start();
        func(args...);
        elapsedTimes.push_back(time.elapsed());
    }

    int max = *std::max_element(elapsedTimes.begin(), elapsedTimes.end());
    int min = *std::min_element(elapsedTimes.begin(), elapsedTimes.end());

    double avg = (std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0)) * 1.0 / iterCount;

    std::cout<<"max: "<<max<<"; min: "<<min<<"; avg: "<<avg<<std::endl;
}


class SolversTest : public QObject
{
    Q_OBJECT

private:
    QStringList filenames = {"samples/1.txt", "samples/2.txt", "samples/numbers_lightest.txt", "samples/numbers_light.txt", "samples/3.txt", "samples/4.txt"};

private slots:
    void correctness(){
        Solver* target = new LongLongSolver();
        Solver* basic = new BasicSolver();


        for (const auto &filename : qAsConst(filenames)){
            std::cout << filename.toStdString() <<'\n';
            QCOMPARE(target->solve(filename), basic->solve(filename));
        }
        //std::cout<<target->solve(filenames[3]).toStdString()<<std::endl;
        //std::cout<<target->solve(filenames[4]).toStdString()<<std::endl;//first_4  = first_3 * 143/13; second_3 value = second_4

        delete target;
        delete basic;
    }
    void timings(){
        Solver* target = new LongLongSolver();
        Solver* basic = new BasicSolver();

        std::cout << "Basic:\n";
        //benchmark(20, [&basic](QString str){basic->solve(str);}, filenames[5]);

        std::cout << "Target:\n";
        //benchmark(20, [&target](QString str){target->solve(str);}, filenames[5]);

        delete target;
        delete basic;
    }

};

#endif // SOLVERTEST_H
