#include <QCoreApplication>
#include <QDebug>
#include "passengervehecle.h"
#include "transportvehecle.h"
#include "filewriter.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Parent object
    QObject vehecleList;

    // Create vehecles
    new PassengerVehecle(&vehecleList);                                      // default
    new TransportVehecle(&vehecleList);                                      // default
    new PassengerVehecle("BMW M4",          2022, 5,       &vehecleList);
    new PassengerVehecle("Mercedes Benz Sprinter",2021, 20,      &vehecleList);
    new PassengerVehecle("Audi A4",           2023, 2,       &vehecleList);
    new TransportVehecle("Volvo FH16",            2020, 25000.0, &vehecleList);
    new TransportVehecle("Ford Transit",          2019, 1500.0,  &vehecleList);
    new PassengerVehecle("", 1800, -3, &vehecleList);                        // defaults

    // Print to console
    qDebug() << "\nVehecle List ";
    const auto vehecles = vehecleList.findChildren<Vehecle*>(
        QString(), Qt::FindDirectChildrenOnly);
    for (const Vehecle* v : vehecles)
        v->printDetails();

    // Build QObjectList for FileWriter
    QObjectList objList;
    for (QObject* child : vehecleList.children())
        objList.append(child);

    // Create FileWriter and write to file
    FileWriter writer(&objList, "vehecles.txt");
    int written = writer.write();

    qDebug() << "\nRecords written to file:" << written;

    return 0;
}
