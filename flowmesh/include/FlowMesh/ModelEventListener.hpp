#ifndef FILAPP_MODELEVENTLISTENER_HPP
#define FILAPP_MODELEVENTLISTENER_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

struct PositionEvent
{
    FGuid fGuid;
    LinAl::Vec3d position;
};

class FlowMeshCone;
class FlowMeshCylinder;
class FlowMeshSegments;
class FlowMeshSphere;
class FlowMeshCuboid;

class ModelEventListener {
  public:
    virtual ~ModelEventListener() = default;

    virtual void onAdd(const FlowMeshCylinder& flowMeshCylinder) {}
    virtual void onAdd(const FlowMeshCone& flowMeshCone) {}
    virtual void onAdd(const FlowMeshSegments& flowMeshSegments) {}
    virtual void onAdd(const FlowMeshSphere& flowMeshSphere) {}
    virtual void onAdd(const FlowMeshCuboid& flowMeshCuboid) {};

    virtual void onRemove(const FGuid& fGuid) {}

    virtual void onPositionChanged(const PositionEvent& positionEvent) {}
};

} // namespace FlowMesh

#endif // FILAPP_MODELEVENTLISTENER_HPP
