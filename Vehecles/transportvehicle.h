#ifndef TRANSPORTVEHICLE_H
#define TRANSPORTVEHICLE_H

#include "vehicles.h"

class TransportVehicle : public Vehicle
{
    Q_OBJECT

public:
    static const double DEFAULT_CAPACITY_KG;
    static constexpr double MIN_CAPACITY_KG = 1.0;
    static constexpr double MAX_CAPACITY_KG = 500000.0;

    explicit TransportVehicle(QObject* parent = nullptr);
    TransportVehicle(const QString& model, int year,
                     double capacityKg, QObject* parent = nullptr);

    double carryingCapacity() const;
    void   setCarryingCapacity(double capacityKg);

    void printDetails() const override;

private:
    double m_carryingCapacity;
};

#endif // TRANSPORTVEHICLE_H
