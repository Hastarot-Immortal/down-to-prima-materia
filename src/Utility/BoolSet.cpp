#include "BoolSet.hpp"

BoolSet::BoolSet()
: bits_(0) {}

BoolSet::BoolSet(std::uint8_t bits)
: bits_(bits) {}

BoolSet::BoolSet(const std::vector<bool>& list)
: bits_(0)
{
    int i = 0;
    for (auto b = list.crbegin(); b != list.crend(); ++b)
    {
        if (i >= 8) break;
        else if (*b) setTrue(i);
        ++i;
    }
}

bool BoolSet::operator[](const int idx) const
{
    return get(idx);
}

bool BoolSet::get(const int idx) const
{
    return (idx <= 7 && idx >= 0) ? (bool)(bits_ >> idx) & 1 : false;
}

void BoolSet::setTrue(const int idx)
{
    if (idx <= 7 && idx >= 0) bits_ |= (1 << idx);
}

void BoolSet::setFalse(const int idx)
{
    if (idx <= 7 && idx >= 0) bits_ &= ~(1 << idx);
}

void BoolSet::flip(const int idx)
{
    if (idx <= 7 && idx >= 0) bits_ ^= (1 << idx);
}
