#include <cstdint>
#include <vector>

class BoolSet
{
private:
    std::uint8_t bits_;
public:
    BoolSet();

    BoolSet(std::uint8_t bits);

    BoolSet(const std::vector<bool>& list);

    bool operator[](const int idx) const;

    bool get(const int idx) const;

    void setTrue(const int idx);

    void setFalse(const int idx);

    void flip(const int idx);
};
