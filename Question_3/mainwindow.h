#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void addRecord();
    void removeRecord();
    void applyFilter();
    void resetFilter();
    void onDataChanged(const QModelIndex& topLeft,
                       const QModelIndex& bottomRight,
                       const QList<int>& roles);

private:
    // Model & proxy
    QStandardItemModel*    m_model;
    QSortFilterProxyModel* m_proxy;

    // View
    QTableView* m_view;

    // Input fields
    QLineEdit* m_authorEdit;
    QSpinBox*  m_yearSpin;
    QLineEdit* m_titleEdit;
    QLineEdit* m_journalEdit;
    QSpinBox*  m_volumeSpin;
    QSpinBox*  m_issueSpin;
    QLineEdit* m_pagesEdit;

    // Filter controls
    QComboBox* m_filterField;
    QLineEdit* m_filterEdit;

    // Helpers
    void setupModel();
    void setupView();
    void setupUI();
    void colorRow(int row);
    void colorAllRows();

    enum Columns { Author=0, Year, Title, Journal, Volume, Issue, Pages };
};

#endif // MAINWINDOW_H
