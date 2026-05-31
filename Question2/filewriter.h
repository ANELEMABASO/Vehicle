#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QObjectList>
#include <QString>

class FileWriter : public QObject
{
    Q_OBJECT

public:
    FileWriter(QObjectList* olist, QString fname, QObject* parent = nullptr);

    int write();

private:
    QObjectList* m_list;
    QString      m_filename;
};

#endif // FILEWRITER_H
