#ifndef MESHLER_MMODELEVENTLISTENER_HPP
#define MESHLER_MMODELEVENTLISTENER_HPP

#include <Core/Types/TVector.hpp>
#include <Meshler/MGuid.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace Meshler
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

    virtual void onAdd(const MCylinder& meshlerCylinder) {}
    virtual void onAdd(const MCone& meshlerCone) {}
    virtual void onAdd(const MSegments& meshlerSegments) {}
    virtual void onAdd(const MSphere& meshlerSphere) {}
    virtual void onAdd(const MCuboid& meshlerCuboid){};
    virtual void onAdd(const MGrid& meshlerGrid){};

    virtual void onPreRemove(const FGuid& guid){};
    virtual void onPostRemove(const FGuid& guid){};

    virtual void onRemove(const FGuid& guid) {}

    virtual void onUpdate(const MCylinder& meshlerCylinder) {}
    virtual void onUpdate(const MCone& meshlerCone) {}
    virtual void onUpdate(const MSegments& meshlerSegments) {}
    virtual void onUpdate(const MSphere& meshlerSphere) {}
    virtual void onUpdate(const MCuboid& meshlerCuboid){};
    virtual void onUpdate(const MGrid& meshlerGrid){};

    virtual void onPositionChanged(const PositionEvent& positionEvent) {}
};

} // namespace Meshler

#endif // MESHLER_MMODELEVENTLISTENER_HPP
