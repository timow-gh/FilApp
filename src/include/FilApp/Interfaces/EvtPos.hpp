#ifndef FILAPP_EVTPOS_HPP
#define FILAPP_EVTPOS_HPP

#include <cstddef>
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT EvtPos
{
    size_t x;
    size_t y;

    EvtPos(size_t x, size_t y) : x(x), y(y) {}
};
} // namespace FilApp

#endif // FILAPP_EVTPOS_HPP
