#include "filereadingtask.h"

#include <QTextStream>

FileReadingTask::FileReadingTask(const QString& filename, QVector<ConcurrentStack<long long int>*> stacks)
    : QObject(NULL)
    , m_file(filename)
    , dataholders(stacks)
{}

void FileReadingTask::run(){
    if (!m_file.open(QIODevice::ReadOnly)){
        emit readingFinished(RESULT_FAILED_OPEN);
        return;
    }

    QVector<int> data;

    QTextStream in(&m_file);
    while(!in.atEnd()){
        QStringList line_array = in.readLine().split(" ");

        bool flag;
        for (QString str : line_array){
            long long int val = str.toLongLong(&flag);

            if (flag)
                emit readingFinished(RESULT_FAILED_READ);

            for (auto holder : dataholders){
                holder->push(val);
            }
        }
    }
    emit readingFinished(RESULT_SUCCESS);

    return;
}
