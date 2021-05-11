#include "filereadingtask.h"

#include <QTextStream>

FileReadingTask::FileReadingTask(const QString& filename, QVector<ConcurrentStack<QString>*> stacks)
    : QObject(NULL)
    , m_file(filename)
    , dataholders(stacks)
{}

void FileReadingTask::run(){
    if (!m_file.open(QIODevice::ReadOnly)){
        emit readingFinished(RESULT_FAILED_OPEN);
        return;
    }

    //QVector<int> data;

    QTextStream in(&m_file);
    while(!in.atEnd()){
        QString str(in.readLine());
        for (auto holder : qAsConst(dataholders)){
            holder->push(str);
        }

    }
    emit readingFinished(RESULT_SUCCESS);

    return;
}
