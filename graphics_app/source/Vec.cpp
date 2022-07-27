#include <Graphics/Vec.hpp>
#include <iostream>

namespace Graphics
{
template <std::size_t SIZE>
std::ostream& operator<<(std::ostream& os, const Vec<SIZE>& vec)
{
    return os << vec[0] << ", " << vec[1] << ", " << vec[2];
}
} // namespace Graphics
