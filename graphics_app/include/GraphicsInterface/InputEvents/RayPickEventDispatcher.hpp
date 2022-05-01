#ifndef FILAPP_RAYPICKEVENTDISPATCHER_HPP
#define FILAPP_RAYPICKEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>

namespace Graphics
{

class RayPickEventDispatcher {
    std::vector<RayPickEventListener*> m_listener;

    template <typename TMessage>
    void dispatchImpl(const TMessage& message)
    {
        for (RayPickEventListener* listener: m_listener)
            listener->onEvent(message);
    }

  public:
    void registerRayPickEventListener(RayPickEventListener* listener)
    {
        m_listener.push_back(listener);
    }

    void removeRayPickEventListener(RayPickEventListener* listener)
    {
        auto iter = std::remove(m_listener.begin(), m_listener.end(), listener);
        if (iter != m_listener.cend())
        {
            listener->onRemoveRayPickEventListener();
            m_listener.erase(iter, m_listener.end());
        }
    }

    void dispatch(const PickRayEvent& pickRayEvent) { dispatchImpl(pickRayEvent); }
    void dispatch(const PickRayMoveEvent& pickRayMoveEvent) { dispatchImpl(pickRayMoveEvent); }
};
} // namespace Graphics

#endif // FILAPP_RAYPICKEVENTDISPATCHER_HPP
