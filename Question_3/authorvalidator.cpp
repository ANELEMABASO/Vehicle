#include "authorvalidator.h"

#include <utility>

class authorvalidatorData : public QSharedData
{
public:
};

authorvalidator::authorvalidator()
    : data(new authorvalidatorData)
{}

authorvalidator::authorvalidator(const authorvalidator &rhs)
    : data{rhs.data}
{}

authorvalidator::authorvalidator(authorvalidator &&rhs)
    : data{std::move(rhs.data)}
{}

authorvalidator &authorvalidator::operator=(const authorvalidator &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

authorvalidator &authorvalidator::operator=(authorvalidator &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

authorvalidator::~authorvalidator() = default;
