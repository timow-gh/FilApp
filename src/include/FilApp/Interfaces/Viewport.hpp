#ifndef FILAPP_VIEWPORT_HPP
#define FILAPP_VIEWPORT_HPP

#include <cstdint>
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT Viewport
{
    int32_t left;
    int32_t bottom;
    uint32_t width;
    uint32_t height;
    Viewport(int32_t left, int32_t bottom, uint32_t width, uint32_t height)
        : left(left), bottom(bottom), width(width), height(height)
    {
    }

};
} // namespace FilApp

#endif // FILAPP_VIEWPORT_HPP
