#include <QTest>

#include "solvertest.h"

int main()
{
    QTest::qExec(new SolversTest);

    return 0;
}
