#include "mainwindow.h"
#include "yeardelegate.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QDate>
#include <QMessageBox>
#include <QStandardItem>
#include <QGroupBox>

// Column headers
static const QStringList HEADERS = {
    "Author", "Year", "Title", "Journal", "Volume", "Issue", "Pages"
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupModel();
    setupView();
    setupUI();
    setWindowTitle("Journals");
    resize(900, 500);
}

// Model setup
void MainWindow::setupModel()
{
    m_model = new QStandardItemModel(0, 7, this);
    m_model->setHorizontalHeaderLabels(HEADERS);

    // Proxy for sorting + filtering
    m_proxy = new QSortFilterProxyModel(this);
    m_proxy->setSourceModel(m_model);
    m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxy->setFilterKeyColumn(Author); // default filter on Author

    // React to data changes (e.g. year edited in view)
    connect(m_model, &QStandardItemModel::dataChanged,
            this,    &MainWindow::onDataChanged);
}

// View setup
void MainWindow::setupView()
{
    m_view = new QTableView(this);
    m_view->setModel(m_proxy);
    m_view->setSortingEnabled(true);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->horizontalHeader()->setStretchLastSection(true);
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    m_view->verticalHeader()->setVisible(false);
    m_view->setAlternatingRowColors(false); // we handle colours manually

    // Attach year delegate to Year column only
    m_view->setItemDelegateForColumn(Year, new YearDelegate(this));
}

//UI layout
void MainWindow::setupUI()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    //Left panel: input form
    m_authorEdit  = new QLineEdit;
    m_yearSpin    = new QSpinBox;
    m_yearSpin->setRange(1000, QDate::currentDate().year());
    m_yearSpin->setValue(1900);
    m_titleEdit   = new QLineEdit;
    m_journalEdit = new QLineEdit;
    m_volumeSpin  = new QSpinBox;
    m_volumeSpin->setRange(0, 9999);
    m_issueSpin   = new QSpinBox;
    m_issueSpin->setRange(0, 9999);
    m_pagesEdit   = new QLineEdit;

    QFormLayout* form = new QFormLayout;
    form->addRow("Author",  m_authorEdit);
    form->addRow("Year",    m_yearSpin);
    form->addRow("Title",   m_titleEdit);
    form->addRow("Journal", m_journalEdit);
    form->addRow("Volume",  m_volumeSpin);
    form->addRow("Issue",   m_issueSpin);
    form->addRow("Pages",   m_pagesEdit);

    QPushButton* addBtn    = new QPushButton("Add");
    QPushButton* removeBtn = new QPushButton("Remove");

    connect(addBtn,    &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::removeRecord);

    // Left panel: filter
    // Pages excluded from filter fields per spec
    m_filterField = new QComboBox;
    m_filterField->addItems({"Author","Year","Title","Journal","Volume","Issue"});

    m_filterEdit = new QLineEdit;
    m_filterEdit->setPlaceholderText("Wildcard filter (e.g. A*)");

    QPushButton* findBtn  = new QPushButton("Find");
    QPushButton* resetBtn = new QPushButton("Reset");

    connect(findBtn,  &QPushButton::clicked, this, &MainWindow::applyFilter);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::resetFilter);

    //Assemble left panel
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addLayout(form);
    leftLayout->addWidget(addBtn);
    leftLayout->addWidget(removeBtn);
    leftLayout->addStretch();
    leftLayout->addWidget(m_filterField);
    leftLayout->addWidget(m_filterEdit);

    QHBoxLayout* filterBtnLayout = new QHBoxLayout;
    filterBtnLayout->addWidget(findBtn);
    filterBtnLayout->addWidget(resetBtn);
    leftLayout->addLayout(filterBtnLayout);

    QWidget* leftPanel = new QWidget;
    leftPanel->setFixedWidth(200);
    leftPanel->setLayout(leftLayout);

    //Main layout
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(m_view);
}

//Row colour helper
void MainWindow::colorRow(int row)
{
    int currentYear = QDate::currentDate().year();
    int year = m_model->item(row, Year)->text().toInt();
    int age  = currentYear - year;

    QColor color;
    if (age > 10)
        color = QColor(255, 180, 180); // red — older than 10 years
    else if (age <= 5)
        color = QColor(180, 255, 180); // green — within last 5 years
    else
        color = QColor(Qt::white);     // no highlight — between 6-10 years

    for (int col = 0; col < m_model->columnCount(); col++) {
        QStandardItem* item = m_model->item(row, col);
        if (item)
            item->setBackground(color);
    }
}

void MainWindow::colorAllRows()
{
    for (int row = 0; row < m_model->rowCount(); row++)
        colorRow(row);
}

//Add record
void MainWindow::addRecord()
{
    int currentYear = QDate::currentDate().year();
    int year = m_yearSpin->value();

    if (year > currentYear)
    {
        QMessageBox::warning(this, "Invalid Year",
                             QString("Year cannot be later than %1.").arg(currentYear));
        return;
    }

    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(m_authorEdit->text())
             << new QStandardItem(QString::number(year))
             << new QStandardItem(m_titleEdit->text())
             << new QStandardItem(m_journalEdit->text())
             << new QStandardItem(QString::number(m_volumeSpin->value()))
             << new QStandardItem(QString::number(m_issueSpin->value()))
             << new QStandardItem(m_pagesEdit->text());

    // Make year item sort numerically
    rowItems[Year]->setData(year, Qt::UserRole);

    m_model->appendRow(rowItems);
    colorRow(m_model->rowCount() - 1);

    // Clear inputs
    m_authorEdit->clear();
    m_yearSpin->setValue(1900);
    m_titleEdit->clear();
    m_journalEdit->clear();
    m_volumeSpin->setValue(0);
    m_issueSpin->setValue(0);
    m_pagesEdit->clear();
}

//Remove record
void MainWindow::removeRecord()
{
    QModelIndex proxyIndex = m_view->currentIndex();
    if (!proxyIndex.isValid()) {
        QMessageBox::information(this, "Remove", "Please select a row to remove.");
        return;
    }
    // Map proxy index back to source model
    QModelIndex sourceIndex = m_proxy->mapToSource(proxyIndex);
    m_model->removeRow(sourceIndex.row());
}

//Filter
void MainWindow::applyFilter()
{
    QString pattern = m_filterEdit->text();

    // Convert wildcard (*,?) to regex
    // QSortFilterProxyModel supports QRegularExpression
    QString regexPattern = QRegularExpression::wildcardToRegularExpression(pattern);
    m_proxy->setFilterRegularExpression(
        QRegularExpression(regexPattern, QRegularExpression::CaseInsensitiveOption));

    // Map combo text to column index (Pages excluded so offset matches)
    QStringList filterFields = {"Author","Year","Title","Journal","Volume","Issue"};
    int col = filterFields.indexOf(m_filterField->currentText());
    m_proxy->setFilterKeyColumn(col);
}

void MainWindow::resetFilter()
{
    m_filterEdit->clear();
    m_proxy->setFilterRegularExpression(QRegularExpression());
}

//Handle in-view year edits
void MainWindow::onDataChanged(const QModelIndex& topLeft,
                               const QModelIndex& bottomRight,
                               const QList<int>&)
{
    // Recolour any row that was changed
    for (int row = topLeft.row(); row <= bottomRight.row(); row++)
        colorRow(row);
}
