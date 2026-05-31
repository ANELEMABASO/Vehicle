#include "authorvalidator.h"
#include <QRegularExpression>

AuthorValidator::AuthorValidator(QObject* parent)
    : QValidator(parent) {}

QValidator::State AuthorValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)

    if (input.isEmpty())
        return Intermediate; // allow empty while typing

    // Only letters (Unicode), spaces, hyphens allowed
    static const QRegularExpression validChars(
        R"(^[\p{L}\s\-]+$)");

    if (!validChars.match(input).hasMatch())
        return Invalid;

    // Must start with a letter (not a space or hyphen)
    if (!input[0].isLetter())
        return Intermediate;

    return Acceptable;
}

void AuthorValidator::fixup(QString& input) const
{
    // Remove any character that isn't a letter, space, or hyphen
    static const QRegularExpression invalidChars(R"([^\p{L}\s\-])");
    input.remove(invalidChars);
    input = input.trimmed();
}