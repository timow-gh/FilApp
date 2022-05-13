#ifndef FILAPP_MODELEVENTLISTENER_HPP
#define FILAPP_MODELEVENTLISTENER_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
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
class FlowMeshGrid;

class ModelEventListener {
  public:
    virtual ~ModelEventListener() = default;

    virtual void onPreAddEvent(){};
    virtual void onModelPostAddEvent(){};

    virtual void onAdd(const FlowMeshCylinder& flowMeshCylinder) {}
    virtual void onAdd(const FlowMeshCone& flowMeshCone) {}
    virtual void onAdd(const FlowMeshSegments& flowMeshSegments) {}
    virtual void onAdd(const FlowMeshSphere& flowMeshSphere) {}
    virtual void onAdd(const FlowMeshCuboid& flowMeshCuboid){};
    virtual void onAdd(const FlowMeshGrid& flowMeshGrid){};

    virtual void onPreRemove(const FGuid& guid){};
    virtual void onPostRemove(const FGuid& guid){};

    virtual void onRemove(const FGuid& guid) {}

    virtual void onUpdate(const FlowMeshCylinder& flowMeshCylinder) {}
    virtual void onUpdate(const FlowMeshCone& flowMeshCone) {}
    virtual void onUpdate(const FlowMeshSegments& flowMeshSegments) {}
    virtual void onUpdate(const FlowMeshSphere& flowMeshSphere) {}
    virtual void onUpdate(const FlowMeshCuboid& flowMeshCuboid){};
    virtual void onUpdate(const FlowMeshGrid& flowMeshGrid){};

    virtual void onPositionChanged(const PositionEvent& positionEvent) {}
};

} // namespace FlowMesh

#endif // FILAPP_MODELEVENTLISTENER_HPP
