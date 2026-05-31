#include "transportvehecle.h"
#include <QDebug>

const double TransportVehecle::DEFAULT_CAPACITY_KG = 1000.0;

TransportVehecle::TransportVehecle(QObject* parent)
    : Vehecle(parent),
    m_carryingCapacity(DEFAULT_CAPACITY_KG)
{}

TransportVehecle::TransportVehecle(const QString& model, int year,
                                   double capacityKg, QObject* parent)
    : Vehecle(model, year, parent),
    m_carryingCapacity(DEFAULT_CAPACITY_KG)
{
    setCarryingCapacity(capacityKg);
}

double TransportVehecle::carryingCapacity() const { return m_carryingCapacity; }

void TransportVehecle::setCarryingCapacity(double capacityKg)
{
    if (capacityKg >= MIN_CAPACITY_KG && capacityKg <= MAX_CAPACITY_KG)
        m_carryingCapacity = capacityKg;
    else
        qWarning() << "Capacity" << capacityKg
                   << "kg out of range. Keeping current value:" << m_carryingCapacity;
}
//Detailing vehecle
void TransportVehecle::printDetails() const
{
    qDebug() << "[Transport Vehecle]"
             << "Model:"    << model()
             << "| Year:"   << year()
             << "| Capacity:" << m_carryingCapacity << "kg";
}