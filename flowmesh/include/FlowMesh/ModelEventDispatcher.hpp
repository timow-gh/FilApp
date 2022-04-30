#ifndef FILAPP_MODELEVENTDISPATCHER_HPP
#define FILAPP_MODELEVENTDISPATCHER_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/ModelEventListener.hpp>
#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

class FlowMeshCone;
class FlowMeshCylinder;
class FlowMeshSegments;
class FlowMeshSphere;
class PositionEvent;

class ModelEventDispatcher {
    std::vector<ModelEventListener*> m_listeners;

    template <typename TMessage>
    void dispatchAddImpl(const TMessage& message)
    {
        for (ModelEventListener* listener: m_listeners)
            listener->onAdd(message);
    }

  public:
    void registerListener(ModelEventListener* listener) { m_listeners.push_back(listener); }
    void removeListener(ModelEventListener* listener)
    {
        auto iter = std::remove(m_listeners.begin(), m_listeners.end(), listener);
        m_listeners.erase(iter, m_listeners.end());
    }

    virtual void dispatchAdd(const FlowMeshCylinder& flowMeshCylinder)
    {
        dispatchAddImpl(flowMeshCylinder);
    }

    virtual void dispatchAdd(const FlowMeshCone& flowMeshCone) { dispatchAddImpl(flowMeshCone); }

    virtual void dispatchAdd(const FlowMeshSegments& flowMeshSegments)
    {
        dispatchAddImpl(flowMeshSegments);
    }

    virtual void dispatchAdd(const FlowMeshSphere& flowMeshSphere)
    {
        dispatchAddImpl(flowMeshSphere);
    }

    virtual void dispatchAdd(const FlowMeshCuboid& flowMeshCuboid)
    {
        dispatchAddImpl(flowMeshCuboid);
    }

    virtual void dispatchAdd(const FlowMeshGrid& flowMeshGrid)
    {
        dispatchAddImpl(flowMeshGrid);
    }

    virtual void dispatchRemove(const FGuid& fGuid)
    {
        for (ModelEventListener* listener: m_listeners)
            listener->onRemove(fGuid);
    }

    virtual void dispatchPositionChanged(const PositionEvent& positionEvent)
    {
        for (ModelEventListener* listener: m_listeners)
            listener->onPositionChanged(positionEvent);
    }
};

} // namespace FlowMesh

#endif // FILAPP_MODELEVENTDISPATCHER_HPP
