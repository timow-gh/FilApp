#ifndef FILAPP_VEC_HPP
#define FILAPP_VEC_HPP

#include <cmath>

namespace FilApp
{
template <std::size_t SIZE>
struct Vec
{
    float_t values[SIZE];

    template <typename... Args>
    Vec(Args... args) : values{args...}
    {
    }

    [[nodiscard]] inline uint8_t size() const noexcept { return SIZE; }
    [[nodiscard]] inline float_t operator[](std::size_t i) const noexcept
    {
        return values[i];
    }
    inline float_t& operator[](std::size_t i) noexcept { return values[i]; }
};

// clang-format off
struct Vec3 : public Vec<3>{using Vec<3>::Vec;};
struct Vec4 : public Vec<4>{using Vec<4>::Vec;};
// clang-format on
} // namespace FilApp

#endif // FILAPP_VEC_HPP
