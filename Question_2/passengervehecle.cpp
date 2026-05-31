#include "passengervehecle.h"
#include <QDebug>

PassengerVehecle::PassengerVehecle(QObject* parent)
    : Vehecle(parent),
    m_passengerCapacity(DEFAULT_PASSENGERS)
{}

PassengerVehecle::PassengerVehecle(const QString& model, int year,
                                   int passengers, QObject* parent)
    : Vehecle(model, year, parent),
    m_passengerCapacity(DEFAULT_PASSENGERS)
{
    setPassengerCapacity(passengers);
}

int PassengerVehecle::passengerCapacity() const { return m_passengerCapacity; }

void PassengerVehecle::setPassengerCapacity(int passengers)
{
    if (passengers >= MIN_PASSENGERS && passengers <= MAX_PASSENGERS)
        m_passengerCapacity = passengers;
    else
        qWarning() << "Passenger count" << passengers
                   << "out of range. Keeping current value:" << m_passengerCapacity;
}
//Vehecle detailing
void PassengerVehecle::printDetails() const
{
    qDebug() << "[Passenger Vehecle]"
             << "Model:"       << model()
             << "| Year:"      << year()
             << "| Passengers:" << m_passengerCapacity;
}