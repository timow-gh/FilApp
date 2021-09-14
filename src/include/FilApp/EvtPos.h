#ifndef FILAPP_EVTPOS_H
#define FILAPP_EVTPOS_H

namespace FilApp
{
struct FILAPP_EXPORT EvtPos
{
    size_t _x{};
    size_t _y{};

    EvtPos(size_t x, size_t y) : x(x), y(y) {}
};
} // namespace FilApp

#endif // FILAPP_EVTPOS_H
