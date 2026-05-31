#ifndef TITLEVALIDATOR_H
#define TITLEVALIDATOR_H

#include <QValidator>

// Valid: words containing ONLY letters OR only digits it not  mixed in same word
// "Journal of Science 2024" → OK
// "3D Graphics"             → NOT OK (3D mixes digit and letter)
// Allowed characters: letters, digits, spaces
class TitleValidator : public QValidator
{
    Q_OBJECT
public:
    explicit TitleValidator(QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override;
    void  fixup(QString& input)              const override;

private:
    bool hasInvalidWord(const QString& input) const;
};

#endif // TITLEVALIDATOR_H
