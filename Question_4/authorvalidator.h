#ifndef AUTHORVALIDATOR_H
#define AUTHORVALIDATOR_H

#include <QValidator>

// Valid: "SZ Mbanjwa-Mhlana"
// Rules:
//   - Letters (including accented), spaces, hyphens only
//   - No digits, no full stops, no other special characters
class AuthorValidator : public QValidator
{
    Q_OBJECT
public:
    explicit AuthorValidator(QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override;
    void  fixup(QString& input)              const override;
};

#endif // AUTHORVALIDATOR_H
