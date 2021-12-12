#ifndef FILAPP_RAYPICKEVENTDISPATCHER_HPP
#define FILAPP_RAYPICKEVENTDISPATCHER_HPP

#include <FilAppInterfaces/InputEvents/DispatcherBase.hpp>

namespace FilApp
{
class RayPickEventListener;

class RayPickEventDispatcher : public DispatcherBase<RayPickEventListener> {
  public:
    using DispatcherBase<RayPickEventListener>::DispatcherBase;
};
} // namespace FilApp

#endif // FILAPP_RAYPICKEVENTDISPATCHER_HPP
