#ifndef FILEREADINGTASK_H
#define FILEREADINGTASK_H

#include <QObject>
#include <QRunnable>
#include <QFile>

#include "concurrentlist.h"

//Runnable class to read data from file
class FileReadingTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    enum ResultCode{
        RESULT_SUCCESS,
        RESULT_FAILED_OPEN,
        RESULT_FAILED_READ
    };

public:
    FileReadingTask(const QString& filename, QVector<ConcurrentStack<QString>*> stacks);

    void run();

signals:
    void readingFinished(int resultCode);

private:
    QFile m_file;
    QVector<ConcurrentStack<QString>*> dataholders;

};

#endif // FILEREADINGTASK_H
