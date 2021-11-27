#ifndef FILAPP_VEC3_HPP
#define FILAPP_VEC3_HPP

#include <cmath>

namespace FilApp
{
struct Vec3
{
    float_t x;
    float_t y;
    float_t z;

    Vec3(const float_t& x, const float_t& y, const float_t& z)
        : x(x), y(y), z(z)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_VEC3_HPP
