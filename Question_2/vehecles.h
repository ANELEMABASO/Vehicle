#ifndef VEHECLES_H
#define VEHECLES_H

#include <QObject>
#include <QString>

class Vehecle : public QObject
{
    Q_OBJECT

    // Declare properties for reflection
    Q_PROPERTY(QString model READ model WRITE setModel)
    Q_PROPERTY(int year READ year WRITE setYear)

public:
    static const int   DEFAULT_YEAR  = 2000;
    static const int   MIN_YEAR      = 1886;
    static const int   MAX_YEAR      = 2100;
    static const char* DEFAULT_MODEL;

    explicit Vehecle(QObject* parent = nullptr);
    Vehecle(const QString& model, int year, QObject* parent = nullptr);

    QString model() const;
    int     year()  const;
    void    setModel(const QString& model);
    void    setYear(int year);

    virtual void printDetails() const = 0;
    virtual ~Vehecle() = default;

private:
    QString m_model;
    int     m_year;
};

#endif // VEHECLES_H
