#include <QCoreApplication>

#include "taskmanager.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    TaskManager* solver = new TaskManager();
    solver->start(argv[1]);

    //return a.exec();
    return 0;
}
