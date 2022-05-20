#ifndef MESHLER_MMODELEVENTLISTENER_HPP
#define MESHLER_MMODELEVENTLISTENER_HPP

#include <Core/Types/TVector.hpp>
#include <Meshler/MGuid.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

struct PositionEvent
{
    FGuid fGuid;
    LinAl::Vec3d position;
};

class MCone;
class MCylinder;
class MSegments;
class MSphere;
class MCuboid;
class MGrid;

class MModelEventListener {
  public:
    virtual ~MModelEventListener() = default;

    virtual void onPreAddEvent(){};
    virtual void onModelPostAddEvent(){};

    virtual void onAdd(const MCylinder& flowMeshCylinder) {}
    virtual void onAdd(const MCone& flowMeshCone) {}
    virtual void onAdd(const MSegments& flowMeshSegments) {}
    virtual void onAdd(const MSphere& flowMeshSphere) {}
    virtual void onAdd(const MCuboid& flowMeshCuboid){};
    virtual void onAdd(const MGrid& flowMeshGrid){};

    virtual void onPreRemove(const FGuid& guid){};
    virtual void onPostRemove(const FGuid& guid){};

    virtual void onRemove(const FGuid& guid) {}

    virtual void onUpdate(const MCylinder& flowMeshCylinder) {}
    virtual void onUpdate(const MCone& flowMeshCone) {}
    virtual void onUpdate(const MSegments& flowMeshSegments) {}
    virtual void onUpdate(const MSphere& flowMeshSphere) {}
    virtual void onUpdate(const MCuboid& flowMeshCuboid){};
    virtual void onUpdate(const MGrid& flowMeshGrid){};

    virtual void onPositionChanged(const PositionEvent& positionEvent) {}
};

} // namespace FlowMesh

#endif // MESHLER_MMODELEVENTLISTENER_HPP
