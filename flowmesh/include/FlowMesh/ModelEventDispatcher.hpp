#ifndef FILAPP_MODELEVENTDISPATCHER_HPP
#define FILAPP_MODELEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/ModelEventListener.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

class FlowMeshCone;
class FlowMeshCylinder;
class FlowMeshSegments;
class FlowMeshSphere;
class PositionEvent;

class ModelEventDispatcher {
    Core::TVector<ModelEventListener*> m_listeners;

  public:
    void registerListener(ModelEventListener* listener) { m_listeners.push_back(listener); }
    void removeListener(ModelEventListener* listener)
    {
        auto iter = std::remove(m_listeners.begin(), m_listeners.end(), listener);
        m_listeners.erase(iter, m_listeners.end());
    }

    template <typename TGeometryElement>
    void dispatchAdd(const TGeometryElement& element)
    {
        for (ModelEventListener* listener: m_listeners)
        {
            listener->onPreAddEvent();
            listener->onAdd(element);
            listener->onModelPostAddEvent();
        }
    }

    void dispatchRemove(const FGuid& fGuid)
    {
        for (ModelEventListener* listener: m_listeners)
        {
            listener->onPreRemove(fGuid);
            listener->onRemove(fGuid);
            listener->onPostRemove(fGuid);
        }
    }

    template <typename TGeometryElement>
    void dispatchUpdate(const TGeometryElement& element)
    {
        for (ModelEventListener* listener: m_listeners)
            listener->onUpdate(element);
    }

    void dispatchPositionChanged(const PositionEvent& positionEvent)
    {
        for (ModelEventListener* listener: m_listeners)
            listener->onPositionChanged(positionEvent);
    }
};

} // namespace FlowMesh

#endif // FILAPP_MODELEVENTDISPATCHER_HPP
