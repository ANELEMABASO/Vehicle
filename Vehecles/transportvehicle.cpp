#include "transportvehicle.h"
#include <QDebug>

const double TransportVehicle::DEFAULT_CAPACITY_KG = 1000.0;

TransportVehicle::TransportVehicle(QObject* parent)
    : Vehicle(parent),
    m_carryingCapacity(DEFAULT_CAPACITY_KG)
{}

TransportVehicle::TransportVehicle(const QString& model, int year,
                                   double capacityKg, QObject* parent)
    : Vehicle(model, year, parent),
    m_carryingCapacity(DEFAULT_CAPACITY_KG)
{
    setCarryingCapacity(capacityKg);
}

double TransportVehicle::carryingCapacity() const { return m_carryingCapacity; }

void TransportVehicle::setCarryingCapacity(double capacityKg)
{
    if (capacityKg >= MIN_CAPACITY_KG && capacityKg <= MAX_CAPACITY_KG)
        m_carryingCapacity = capacityKg;
    else
        qWarning() << "Capacity" << capacityKg
                   << "kg out of range. Keeping current value:" << m_carryingCapacity;
}
//detailing function
void TransportVehicle::printDetails() const
{
    qDebug() << "[Transport Vehicle]"
             << "Model:"    << model()
             << "| Year:"   << year()
             << "| Capacity:" << m_carryingCapacity << "kg";
}