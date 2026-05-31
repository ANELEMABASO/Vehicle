#include "filewriter.h"
#include <QFile>
#include <QTextStream>
#include <QMetaObject>
#include <QMetaProperty>

FileWriter::FileWriter(QObjectList* olist, QString fname)
    : list(olist), filename(fname) {}

int FileWriter::write()
{
    QFile file(filename);

    // Open file for writing
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return 0;
    }

    QTextStream out(&file);
    int count = 0;

    for (QObject* obj : *list)
    {
        if (!obj)
            continue;

        // Use meta-object to get the class name (type of vehicle)
        const QMetaObject* metaObj = obj->metaObject();
        out << "Vehicle Type: " << metaObj->className() << "\n";

        // Iterate over all properties using reflection
        // Start at 1 to skip QObject's own "objectName" property
        for (int i = 1; i < metaObj->propertyCount(); ++i)
        {
            QMetaProperty prop = metaObj->property(i);
            const char* propName = prop.name();
            QVariant propValue = prop.read(obj);

            out << "  " << propName << ": " << propValue.toString() << "\n";
        }

        out << "\n"; // Blank line between records
        count++;
    }

    file.close();
    return count;
}
