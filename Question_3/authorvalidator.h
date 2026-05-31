#ifndef AUTHORVALIDATOR_H
#define AUTHORVALIDATOR_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class authorvalidatorData;

class authorvalidator
{
    Q_OBJECT
    QML_ELEMENT
public:
    authorvalidator();
    authorvalidator(const authorvalidator &);
    authorvalidator(authorvalidator &&);
    authorvalidator &operator=(const authorvalidator &);
    authorvalidator &operator=(authorvalidator &&);
    ~authorvalidator();

private:
    QSharedDataPointer<authorvalidatorData> data;
};

#endif // AUTHORVALIDATOR_H
