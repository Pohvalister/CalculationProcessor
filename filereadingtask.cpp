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

    //QVector<int> data;

    QTextStream in(&m_file);
    while(!in.atEnd()){
        QStringList line_array = in.readLine().split(" ");

        bool flag;
        for (const QString & str : qAsConst(line_array)){
            long long int val = str.toLongLong(&flag);


            for (auto holder : qAsConst(dataholders)){
                holder->push(val);
            }
        }
    }
    emit readingFinished(RESULT_SUCCESS);

    return;
}
