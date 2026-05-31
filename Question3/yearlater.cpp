#include "yearlater.h"

#include <utility>


class yearLaterData : public QSharedData
{
public:

};

yearLater::yearLater() : data(new yearLaterData)
{

}

yearLater::yearLater(const yearLater &rhs)
    : data{rhs.data}
{

}

yearLater::yearLater(yearLater &&rhs)
    : data{std::move(rhs.data)}
{

}

yearLater &yearLater::operator=(const yearLater &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

yearLater &yearLater::operator=(yearLater &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

yearLater::~yearLater() = default;
