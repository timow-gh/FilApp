#ifndef GRAPHICS_VEC_HPP
#define GRAPHICS_VEC_HPP

#include <Core/Utils/Compiler.hpp>
#include <cmath>
#include <iostream>

namespace Graphics
{
template <std::size_t SIZE>
struct Vec
{
    float_t values[SIZE];

    template <typename... Args>
    Vec(Args... args) : values{args...}
    {
    }

    CORE_NODISCARD inline std::size_t size() const noexcept { return SIZE; }
    CORE_NODISCARD inline float_t operator[](std::size_t i) const noexcept { return values[i]; }
    inline float_t& operator[](std::size_t i) noexcept { return values[i]; }

    friend std::ostream& operator<<(std::ostream& os, const Vec<SIZE>& vec)
    {
        return os << vec[0] << ", " << vec[1] << ", " << vec[2];
    }
};

// clang-format off
struct Vec3 : public Vec<3>{using Vec<3>::Vec;};
struct Vec4 : public Vec<4>{using Vec<4>::Vec;};
// clang-format on
} // namespace Graphics

#endif // GRAPHICS_VEC_HPP
