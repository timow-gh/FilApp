
#ifndef FILAPP_VIEWLISTENER_HPP
#define FILAPP_VIEWLISTENER_HPP

#include "ViewEvents.hpp"
#include <filapp_export.h>

namespace FilApp
{
class FILAPP_EXPORT ViewListener
{
  public:
    ~ViewListener() = default;

    virtual void mouseDownEvent(const MouseDownEvent& mouseDownEvent) = 0;
    virtual void mouseUpEvent(const MouseUpEvent& mouseUpEvent) = 0;
    virtual void mouseMovedEvent(const MouseMovedEvent& mouseMovedEvent) = 0;
    virtual void mouseScrollEvent(const MouseScrollEvent& mouseScrollEvent) = 0;
    virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) = 0;
    virtual void keyUpEvent(const KeyUpEvent& keyUpEvent) = 0;
};
} // namespace FilApp
#endif // FILAPP_VIEWLISTENER_HPP
