#include "filewriter.h"
#include <QFile>
#include <QTextStream>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>

FileWriter::FileWriter(QObjectList* olist, QString fname, QObject* parent)
    : QObject(parent),
    m_list(olist),
    m_filename(fname)
{}

int FileWriter::write()
{
    // Open the file for writing
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file:" << m_filename;
        return 0;
    }

    QTextStream out(&file);
    int count = 0;

    for (QObject* obj : *m_list)
    {
        if (!obj) continue;

        //Reflection: gettype of vehicle
        const QMetaObject* meta = obj->metaObject();
        out << "Type: " << meta->className() << "\n";

        // Reflection: iterate all properties
        for (int i = 1; i < meta->propertyCount(); i++)
        {
            QMetaProperty property = meta->property(i);

            // Get property name and value without calling any getter directly
            QString name  = property.name();
            QVariant value = property.read(obj);

            out << "  " << name << ": " << value.toString() << "\n";
        }

        out << "---\n";
        count++;
    }

    file.close();
    qDebug() << "Written to file:" << m_filename;
    return count;
}
