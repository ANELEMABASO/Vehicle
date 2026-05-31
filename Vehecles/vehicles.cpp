#include "vehicles.h"
#include <QDebug>

const char* Vehicle::DEFAULT_MODEL = "Unknown";

Vehicle::Vehicle(QObject* parent)
    : QObject(parent),
    m_model(DEFAULT_MODEL),
    m_year(DEFAULT_YEAR)
{}

Vehicle::Vehicle(const QString& model, int year, QObject* parent)
    : QObject(parent),
    m_model(DEFAULT_MODEL),
    m_year(DEFAULT_YEAR)
{
    setModel(model);
    setYear(year);
}

QString Vehicle::model() const { return m_model; }
int     Vehicle::year()  const { return m_year;  }

void Vehicle::setModel(const QString& model)
{
    if (!model.trimmed().isEmpty())
        m_model = model.trimmed();
    else
        qWarning() << "Invalid model name. Keeping current value:" << m_model;
}

void Vehicle::setYear(int year)
{
    if (year >= MIN_YEAR && year <= MAX_YEAR)
        m_year = year;
    else
        qWarning() << "Year" << year << "out of range. Keeping current value:" << m_year;
}