#include "yeardelegate.h"
#include <QSpinBox>
#include <QDate>
#include <QMessageBox>

YearDelegate::YearDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

QWidget* YearDelegate::createEditor(QWidget* parent,
                                    const QStyleOptionViewItem&,
                                    const QModelIndex&) const
{
    QSpinBox* spin = new QSpinBox(parent);
    spin->setRange(1000, QDate::currentDate().year()); // max = current year
    spin->setFrame(false);
    return spin;
}

void YearDelegate::setEditorData(QWidget* editor,
                                 const QModelIndex& index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox* spin = static_cast<QSpinBox*>(editor);
    spin->setValue(value);
}

void YearDelegate::setModelData(QWidget* editor,
                                QAbstractItemModel* model,
                                const QModelIndex& index) const
{
    QSpinBox* spin = static_cast<QSpinBox*>(editor);
    spin->interpretText();
    int year = spin->value();
    int currentYear = QDate::currentDate().year();

    if (year > currentYear) {
        QMessageBox::warning(nullptr, "Invalid Year",
                             QString("Year cannot be later than %1.").arg(currentYear));
        return; // reject — keep old value
    }
    model->setData(index, year, Qt::EditRole);
}
