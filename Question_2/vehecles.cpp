#include "vehecles.h"
#include <QDebug>

const char* Vehecle::DEFAULT_MODEL = "Unknown";

Vehecle::Vehecle(QObject* parent)
    : QObject(parent),
    m_model(DEFAULT_MODEL),
    m_year(DEFAULT_YEAR)
{}

Vehecle::Vehecle(const QString& model, int year, QObject* parent)
    : QObject(parent),
    m_model(DEFAULT_MODEL),
    m_year(DEFAULT_YEAR)
{
    setModel(model);
    setYear(year);
}

QString Vehecle::model() const { return m_model; }
int     Vehecle::year()  const { return m_year;  }

void Vehecle::setModel(const QString& model)
{
    if (!model.trimmed().isEmpty())
        m_model = model.trimmed();
    else
        qWarning() << "Invalid model name. Keeping current value:" << m_model;
}

void Vehecle::setYear(int year)
{
    if (year >= MIN_YEAR && year <= MAX_YEAR)
        m_year = year;
    else
        qWarning() << "Year" << year << "out of range. Keeping current value:" << m_year;
}