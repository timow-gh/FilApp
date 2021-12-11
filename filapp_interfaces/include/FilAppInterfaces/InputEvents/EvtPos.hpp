#ifndef FILAPP_EVTPOS_HPP
#define FILAPP_EVTPOS_HPP

#include <cstddef>

namespace FilApp
{
struct EvtPos
{
    size_t x{0};
    size_t y{0};

    EvtPos(size_t x, size_t y) : x(x), y(y) {}
};
} // namespace FilApp

#endif // FILAPP_EVTPOS_HPP
