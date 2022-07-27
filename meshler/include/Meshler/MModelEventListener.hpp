#ifndef MESHLER_MMODELEVENTLISTENER_HPP
#define MESHLER_MMODELEVENTLISTENER_HPP

#include <Core/Types/TVector.hpp>
#include <Meshler/MGuid.hpp>

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

    virtual void onPreAddEvent() {}
    virtual void onModelPostAddEvent() {}

    virtual void onAdd(const MCylinder&) {}
    virtual void onAdd(const MCone&) {}
    virtual void onAdd(const MSegments&) {}
    virtual void onAdd(const MSphere&) {}
    virtual void onAdd(const MCuboid&) {}
    virtual void onAdd(const MGrid&) {}

    virtual void onPreRemove(const FGuid&) {}
    virtual void onPostRemove(const FGuid&) {}

    virtual void onRemove(const FGuid&) {}

    virtual void onUpdate(const MCylinder&) {}
    virtual void onUpdate(const MCone&) {}
    virtual void onUpdate(const MSegments&) {}
    virtual void onUpdate(const MSphere&) {}
    virtual void onUpdate(const MCuboid&) {}
    virtual void onUpdate(const MGrid&) {}

    virtual void onPositionChanged(const PositionEvent&) {}
};

} // namespace Meshler

#endif // MESHLER_MMODELEVENTLISTENER_HPP
