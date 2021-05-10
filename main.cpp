#include <QCoreApplication>

#include <iostream>

#include "taskmanager.h"

int main(int argc, char *argv[])
{
    //std::cout<<argc;
    //QCoreApplication a(argc, argv);
    TaskManager* solver = new TaskManager();
    QString filename = "numbers_da_lightest.txt";
    solver->start(filename);

    //return a.exec();
    return 0;
}
