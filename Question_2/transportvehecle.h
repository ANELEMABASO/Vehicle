#ifndef TRANSPORTVEHICLE_H
#define TRANSPORTVEHICLE_H

#include "vehecles.h"

class TransportVehecle : public Vehecle
{
    Q_OBJECT

    // Declare subclass-specific property
    Q_PROPERTY(double carryingCapacity READ carryingCapacity WRITE setCarryingCapacity)

public:
    static const double DEFAULT_CAPACITY_KG;
    static constexpr double MIN_CAPACITY_KG = 1.0;
    static constexpr double MAX_CAPACITY_KG = 500000.0;

    explicit TransportVehecle(QObject* parent = nullptr);
    TransportVehecle(const QString& model, int year,
                     double capacityKg, QObject* parent = nullptr);

    double carryingCapacity() const;
    void   setCarryingCapacity(double capacityKg);
    void   printDetails() const override;

private:
    double m_carryingCapacity;
};

#endif // TRANSPORTVEHECLE_H

