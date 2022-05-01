#ifndef FILAPP_INPUTEVENTDISPATCHER_HPP
#define FILAPP_INPUTEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/MouseButtonEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseWheelEvent.hpp>

namespace Graphics
{

class InputEventDispatcher {
    Core::TVector<InputEventListener*> m_listener;

    template <typename TMessage>
    void dispatchImpl(const TMessage& message)
    {
        for (InputEventListener* listener: m_listener)
            listener->onEvent(message);
    }

  public:
    void registerInputEventListener(InputEventListener* listener)
    {
        m_listener.push_back(listener);
    }

    void removeInputEventListener(InputEventListener* listener)
    {
        auto iter = std::remove(m_listener.begin(), m_listener.end(), listener);
        if (iter != m_listener.cend())
        {
            listener->onRemoveInputEventListener();
            m_listener.erase(iter, m_listener.end());
        }
    }

    void dispatch(const MouseButtonEvent& mouseButtonEvent) { dispatchImpl(mouseButtonEvent); };
    void dispatch(const MouseMoveEvent& mouseMovedEvent) { dispatchImpl(mouseMovedEvent); };
    void dispatch(const MouseWheelEvent& mouseWheelEvent) { dispatchImpl(mouseWheelEvent); };
    void dispatch(const KeyEvent& keyEvent) { dispatchImpl(keyEvent); }
};
} // namespace Graphics

#endif // FILAPP_INPUTEVENTDISPATCHER_HPP
