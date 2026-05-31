#ifndef YEARLATER_H
#define YEARLATER_H

#include <QStyledItemDelegate>

// Custom delegate to validate year column editing
// Prevents years later than the current year
class Yearlater : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Yearlater(QObject* parent = nullptr);

    QWidget*  createEditor(QWidget* parent,
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override;

    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;
};

#endif // YEARDELEGATE_H
