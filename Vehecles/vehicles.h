#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QString>

class Vehicle : public QObject
{
    Q_OBJECT

public:
    static const int    DEFAULT_YEAR  = 2000;
    static const int    MIN_YEAR      = 1886; // Year of first automobile
    static const int    MAX_YEAR      = 2100;
    static const char*  DEFAULT_MODEL;

    explicit Vehicle(QObject* parent = nullptr);
    Vehicle(const QString& model, int year, QObject* parent = nullptr);

    // Getters
    QString model() const;
    int     year()  const;

    // Setters
    void setModel(const QString& model);
    void setYear(int year);

    // Pure virtual — each subclass defines its own output
    virtual void printDetails() const = 0;

    virtual ~Vehicle() = default;

private:
    QString m_model;
    int     m_year;
};

#endif // VEHICLE_H
