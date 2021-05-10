#ifndef SOLVERTEST_H
#define SOLVERTEST_H

#include <QObject>
#include <QTest>

#include <iostream>

#include "../solvers.h"
#include "basic_solver.h"



class SolversTest : public QObject
{
    Q_OBJECT

private:
    QStringList filenames = {"samples/1.txt", "samples/2.txt", "samples/numbers_lightest.txt", "samples/numbers_light.txt", "samples/3.txt"};

private slots:
    void correctness(){
        Solver* target = new LongLongSolver();
        Solver* basic = new BasicSolver();

        for (auto filename : filenames){
            QCOMPARE(target->solve(filename), basic->solve(filename));
        }
        std::cout<<target->solve(filenames[3]).toStdString()<<std::endl;
        std::cout<<target->solve(filenames[4]).toStdString()<<std::endl;//first_4  = first_3 * 143/13; second_3 value = second_4
    }

};

#endif // SOLVERTEST_H
