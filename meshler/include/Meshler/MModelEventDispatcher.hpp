#ifndef MESHLER_MMODELEVENTDISPATCHER_HPP
#define MESHLER_MMODELEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/MModelEventListener.hpp>

namespace Meshler
{

class MCone;
class MCylinder;
class MSegments;
class MSphere;
class PositionEvent;

class MModelEventDispatcher {
    Core::TVector<MModelEventListener*> m_listeners;

  public:
    void registerListener(MModelEventListener* listener) { m_listeners.push_back(listener); }
    void removeListener(MModelEventListener* listener)
    {
        auto iter = std::remove(m_listeners.begin(), m_listeners.end(), listener);
        m_listeners.erase(iter, m_listeners.end());
    }

    template <typename TGeometryElement>
    void dispatchAdd(const TGeometryElement& element)
    {
        for (MModelEventListener* listener: m_listeners)
        {
            listener->onPreAddEvent();
            listener->onAdd(element);
            listener->onModelPostAddEvent();
        }
    }

    void dispatchRemove(const FGuid& fGuid)
    {
        for (MModelEventListener* listener: m_listeners)
        {
            listener->onPreRemove(fGuid);
            listener->onRemove(fGuid);
            listener->onPostRemove(fGuid);
        }
    }

    template <typename TGeometryElement>
    void dispatchUpdate(const TGeometryElement& element)
    {
        for (MModelEventListener* listener: m_listeners)
            listener->onUpdate(element);
    }

    void dispatchPositionChanged(const PositionEvent& positionEvent)
    {
        for (MModelEventListener* listener: m_listeners)
            listener->onPositionChanged(positionEvent);
    }
};

} // namespace Meshler

#endif // MESHLER_MMODELEVENTDISPATCHER_HPP
