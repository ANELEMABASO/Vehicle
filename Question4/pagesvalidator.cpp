#include "pagesvalidator.h"
#include <QRegularExpression>

PagesValidator::PagesValidator(QObject* parent)
    : QValidator(parent) {}

QValidator::State PagesValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)

    if (input.isEmpty())
        return Intermediate;

    // Partial patterns e.g. "12" or "12-" or "12 -" are Intermediate
    static const QRegularExpression partial(
        R"(^\d+(\s*-?\s*\d*)?$)");

    // Full valid pattern: digits, optional spaces, hyphen, optional spaces, digits
    static const QRegularExpression full(
        R"(^\d+\s*-\s*\d+$)");

    if (full.match(input).hasMatch())
    {
        // Extract both page numbers and validate end >= start
        QRegularExpression nums(R"((\d+)\s*-\s*(\d+))");
        QRegularExpressionMatch m = nums.match(input);
        if (m.hasMatch())
        {
            int startPage = m.captured(1).toInt();
            int endPage   = m.captured(2).toInt();
            if (endPage < startPage)
                return Intermediate; // end page too small — still typing
        }
        return Acceptable;
    }

    if (partial.match(input).hasMatch())
        return Intermediate;

    return Invalid;
}

void PagesValidator::fixup(QString& input) const
{
    // Normalise
    static const QRegularExpression nums(R"((\d+)\s*-\s*(\d+))");
    QRegularExpressionMatch m = nums.match(input);
    if (m.hasMatch())
        input = m.captured(1) + " - " + m.captured(2);
}
