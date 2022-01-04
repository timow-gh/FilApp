#ifndef FILAPP_VIEWPORT_HPP
#define FILAPP_VIEWPORT_HPP

#include <cstdint>

namespace Graphics
{
struct Viewport
{
    int32_t left;
    int32_t bottom;
    uint32_t width;
    uint32_t height;

    Viewport() : left(0), bottom(0), width(800), height(640) {}
    Viewport(int32_t left, int32_t bottom, uint32_t width, uint32_t height)
        : left(left), bottom(bottom), width(width), height(height)
    {
    }
};
} // namespace Graphics

#endif // FILAPP_VIEWPORT_HPP
