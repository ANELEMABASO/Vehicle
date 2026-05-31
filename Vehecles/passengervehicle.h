#ifndef PASSENGERVEHICLE_H
#define PASSENGERVEHICLE_H

#include "vehicles.h"

class PassengerVehicle : public Vehicle
{
    Q_OBJECT

public:
    static const int DEFAULT_PASSENGERS = 5;
    static const int MIN_PASSENGERS     = 1;
    static const int MAX_PASSENGERS     = 100;

    explicit PassengerVehicle(QObject* parent = nullptr);
    PassengerVehicle(const QString& model, int year,
                     int passengers, QObject* parent = nullptr);

    int  passengerCapacity() const;
    void setPassengerCapacity(int passengers);

    void printDetails() const override;

private:
    int m_passengerCapacity;
};

#endif // PASSENGERVEHICLE_H
