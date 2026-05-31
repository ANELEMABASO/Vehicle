#ifndef PAGESVALIDATOR_H
#define PAGESVALIDATOR_H

#include <QValidator>

// Valid formats:
//   "12-15"
//   "121 - 155"
// Rules:
//   - One or more digits, optional spaces, hyphen, optional spaces, one or more digits
//   - End page must be >= start page
class PagesValidator : public QValidator
{
    Q_OBJECT
public:
    explicit PagesValidator(QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override;
    void  fixup(QString& input)              const override;
};

#endif // PAGESVALIDATOR_H
