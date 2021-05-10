#ifndef FILEREADINGTASK_H
#define FILEREADINGTASK_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QAtomicInt>

#include "concurrentlist.h"


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
    FileReadingTask(const QString& filename, QVector<ConcurrentStack<int>*> stacks);
    ~FileReadingTask();

    void run();
signals:
    void readingFinished(int resultCode);

private:
    QFile m_file;
    QVector<ConcurrentStack<int>*> dataholders;

};

#endif // FILEREADINGTASK_H
