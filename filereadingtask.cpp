#include "filereadingtask.h"

#include <QTextStream>

FileReadingTask::FileReadingTask(QFile * file, QVector<ConcurrentStack<QString>*> stacks)
    : QObject(NULL)
    , m_file(file)
    , dataholders(stacks)
{}

void FileReadingTask::run(){


    QTextStream in(m_file);
    while(!in.atEnd()){
        QString str(in.readLine());
        for (auto holder : qAsConst(dataholders)){
            holder->push(str);
        }

    }
    emit readingFinished();
}
