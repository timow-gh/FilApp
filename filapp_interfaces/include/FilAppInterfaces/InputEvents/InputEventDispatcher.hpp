#ifndef FILAPP_INPUTEVENTDISPATCHER_HPP
#define FILAPP_INPUTEVENTDISPATCHER_HPP

#include <FilAppInterfaces/InputEvents/DispatcherBase.hpp>

namespace FilApp
{
class InputEventListener;

class InputEventDispatcher : public DispatcherBase<InputEventListener> {
  public:
    using DispatcherBase<InputEventListener>::DispatcherBase;
};
} // namespace FilApp

#endif // FILAPP_INPUTEVENTDISPATCHER_HPP
