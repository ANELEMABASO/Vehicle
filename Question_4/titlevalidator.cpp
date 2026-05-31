#include "titlevalidator.h"
#include <QRegularExpression>

TitleValidator::TitleValidator(QObject* parent)
    : QValidator(parent) {}

// A word is invalid if it contains BOTH letters and digits
bool TitleValidator::hasInvalidWord(const QString& input) const
{
    // Split on whitespace to get individual words
    const QStringList words = input.split(
        QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);

    for (const QString& word : words)
    {
        bool hasLetter = false;
        bool hasDigit  = false;

        for (const QChar& ch : word) {
            if (ch.isLetter()) hasLetter = true;
            if (ch.isDigit())  hasDigit  = true;
            if (hasLetter && hasDigit)
                return true; // mixed word found — invalid
        }
    }
    return false;
}

QValidator::State TitleValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)

    if (input.isEmpty())
        return Intermediate;

    // Only letters, digits, and spaces allowed
    static const QRegularExpression validChars(R"(^[\p{L}0-9\s]*$)");
    if (!validChars.match(input).hasMatch())
        return Invalid;

    // While still typing a word
    // we allow it as Intermediate — only reject complete mixed words
    if (hasInvalidWord(input))
    {
        // Check if the last word is still being typed
        // If input ends with a space, the last word is complete → Invalid
        if (input.endsWith(' '))
            return Invalid;

        // Still typing — could be fixing it
        return Intermediate;
    }

    return Acceptable;
}

void TitleValidator::fixup(QString& input) const
{
    // Remove any character not a letter, digit, or space
    static const QRegularExpression invalidChars(R"([^\p{L}0-9\s])");
    input.remove(invalidChars);

    // Remove words that mix letters and digits
    QStringList words = input.split(
        QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);

    QStringList cleaned;
    for (const QString& word : words)
    {
        bool hasLetter = false, hasDigit = false;
        for (const QChar& ch : word)
        {
            if (ch.isLetter()) hasLetter = true;
            if (ch.isDigit())  hasDigit  = true;
        }
        if (!(hasLetter && hasDigit))
            cleaned << word;
    }
    input = cleaned.join(' ');
}
