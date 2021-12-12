#ifndef FILAPP_PICKINGCONTEXT_HPP
#define FILAPP_PICKINGCONTEXT_HPP

#include <Core/Types/TVector.hpp>
#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <Geometry/Line.hpp>

namespace FlowMesh
{

struct PickingResult
{
    Geometry::Ray3d pickingRay;
    Core::TVector<double_t> pickingOrdinates;
};

class PickingContext : public FilApp::InputEventListener {
    Geometry::Ray3d m_pickingRay;

};

} // namespace FlowMesh

#endif // FILAPP_PICKINGCONTEXT_HPP
