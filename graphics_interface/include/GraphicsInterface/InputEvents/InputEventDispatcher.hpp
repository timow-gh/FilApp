#ifndef FILAPP_INPUTEVENTDISPATCHER_HPP
#define FILAPP_INPUTEVENTDISPATCHER_HPP

#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>

namespace Graphics
{
class InputEventListener;

class InputEventDispatcher : public DispatcherBase<InputEventListener> {
  public:
    using DispatcherBase<InputEventListener>::DispatcherBase;
};
} // namespace FilApp

#endif // FILAPP_INPUTEVENTDISPATCHER_HPP
