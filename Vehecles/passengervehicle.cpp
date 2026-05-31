#include "passengervehicle.h"
#include <QDebug>

PassengerVehicle::PassengerVehicle(QObject* parent)
    : Vehicle(parent),
    m_passengerCapacity(DEFAULT_PASSENGERS)
{}

PassengerVehicle::PassengerVehicle(const QString& model, int year,
                                   int passengers, QObject* parent)
    : Vehicle(model, year, parent),
    m_passengerCapacity(DEFAULT_PASSENGERS)
{
    setPassengerCapacity(passengers);
}

int PassengerVehicle::passengerCapacity() const { return m_passengerCapacity; }

void PassengerVehicle::setPassengerCapacity(int passengers)
{
    if (passengers >= MIN_PASSENGERS && passengers <= MAX_PASSENGERS)
        m_passengerCapacity = passengers;
    else
        qWarning() << "Passenger count" << passengers
                   << "out of range. Keeping current value:" << m_passengerCapacity;
}
//Vehecle details
void PassengerVehicle::printDetails() const
{
    qDebug() << "[Passenger Vehicle]"
             << "Model:"       << model()
             << "| Year:"      << year()
             << "| Passengers:" << m_passengerCapacity;
}