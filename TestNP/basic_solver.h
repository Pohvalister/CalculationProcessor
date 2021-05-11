#ifndef BASICSOLVER_H
#define BASICSOLVER_H

#include <fstream>

#include "../solvers.h"

using namespace std;

class BasicSolver : public Solver{
    QString solve(QString filename){
        ifstream in(filename.toStdString());

        long long int val;
        long long int ADD_answ = 0;
        bool is_first_value = true;
        long long int SUB_answ = 0;
        long long int XOR_answ = 0;

        while(in >> val){
            if (is_first_value){
                is_first_value = !is_first_value;
                SUB_answ = val;
            }else
                SUB_answ -= val;

            XOR_answ ^= val;
            ADD_answ += val;
        }
        QString answer = QString::number(ADD_answ) + ' ' + QString::number(SUB_answ) + ' ' + QString::number(XOR_answ);
        return answer;
    }
};

#endif
