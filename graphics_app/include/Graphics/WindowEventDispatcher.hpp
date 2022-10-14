#ifndef MESHLER_WINDOWEVENTDISPATCHER_HPP
#define MESHLER_WINDOWEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <Graphics/WindowEventListener.hpp>
#include <type_traits>

namespace Graphics
{

// clang-format off
struct WindowCloseEvent {};
struct WindowMinimizeEvent {};
struct WindowMaximizeEvent {};
struct WindowResizeEvent {
  int width;
  int height;
};
// clang-format on

class WindowEventDispatcher {
  Core::TVector<WindowEventListener*> m_listener;

public:
  template <typename TMessage>
  void dispatch(const TMessage& message)
  {
    for (WindowEventListener* listener: m_listener)
      listener->onEvent(message);
  }

  void registerEventListener(WindowEventListener* listener) { m_listener.push_back(listener); }
  void removeEventListener(WindowEventListener* listener)
  {
    auto iter = std::remove(m_listener.begin(), m_listener.end(), listener);
    if (iter != m_listener.cend())
    {
      listener->onRemoveEventListener();
      m_listener.erase(iter, m_listener.end());
    }
  }
};

} // namespace Graphics

#endif // MESHLER_WINDOWEVENTDISPATCHER_HPP
