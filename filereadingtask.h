#ifndef FILEREADINGTASK_H
#define FILEREADINGTASK_H

#include <QObject>
#include <QRunnable>
#include <QFile>

#include "concurrentstack.h"

//Runnable class to read data from file
class FileReadingTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    FileReadingTask(QFile* file, QVector<ConcurrentStack<QString>*> stacks);

    void run();

signals:
    void readingFinished();

private:
    QFile* m_file;
    QVector<ConcurrentStack<QString>*> dataholders;

};

#endif // FILEREADINGTASK_H
