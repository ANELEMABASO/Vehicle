#ifndef PASSENGERVEHICLE_H
#define PASSENGERVEHICLE_H

#include "vehecles.h"

class PassengerVehecle : public Vehecle
{
    Q_OBJECT

    // Declare subclass-specific property
    Q_PROPERTY(int passengerCapacity READ passengerCapacity WRITE setPassengerCapacity)

public:
    static const int DEFAULT_PASSENGERS = 5;
    static const int MIN_PASSENGERS     = 1;
    static const int MAX_PASSENGERS     = 100;

    explicit PassengerVehecle(QObject* parent = nullptr);
    PassengerVehecle(const QString& model, int year,
                     int passengers, QObject* parent = nullptr);

    int  passengerCapacity() const;
    void setPassengerCapacity(int passengers);
    void printDetails() const override;

private:
    int m_passengerCapacity;
};

#endif // PASSENGERVEHECLE_H