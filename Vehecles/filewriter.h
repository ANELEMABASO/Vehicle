#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QObjectList>
#include <QString>

class FileWriter
{
public:
    FileWriter(QObjectList* olist, QString fname);
    int write();

private:
    QObjectList* list;
    QString filename;
};

#endif // FILEWRITER_H
