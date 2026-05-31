#include <QCoreApplication>
#include <QDebug>
#include "passengervehicle.h"
#include "transportvehicle.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Parent object
    QObject vehicleList;

    //Create vehicles

    // Default-constructed vehicles
    auto* defaultPassenger = new PassengerVehicle(&vehicleList);
    auto* defaultTransport = new TransportVehicle(&vehicleList);

    // Parameterised passenger vehicles
    auto* sedan  = new PassengerVehicle("BMW M3",  2022, 5,  &vehicleList);
    auto* bus    = new PassengerVehicle("Mercedes Benz Sprinter", 2021, 20, &vehicleList);
    auto* sports = new PassengerVehicle("Audi A4",   2023, 2,  &vehicleList);

    // Parameterised transport vehicles
    auto* truck  = new TransportVehicle("Volvo FH16",    2020, 25000.0, &vehicleList);
    auto* van    = new TransportVehicle("Ford Transit",  2019, 1500.0,  &vehicleList);

    //Test invalid inputs
    qDebug() << "\nTesting Validation";
    auto* badVehicle = new PassengerVehicle("", 1800, -3, &vehicleList);

    //Output all vehicles
    qDebug() << "\nVehecle List";
    const auto vehicles = vehicleList.findChildren<Vehicle*>(
        QString(), Qt::FindDirectChildrenOnly);

    for (const Vehicle* v : vehicles)
        v->printDetails();

    qDebug() << "\nTotal vehicles:" << vehicles.size();

    return 0; //All children deleted automatically
}
