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

  private:
    void event(const FilApp::MouseDownEvent& mouseDownEvent) override;
    void event(const FilApp::MouseUpEvent& mouseUpEvent) override;
    void event(const FilApp::MouseMoveEvent& mouseMovedEvent) override;
    void event(const FilApp::MouseWheelEvent& mouseWheelEvent) override;
    void event(const FilApp::KeyDownEvent& keyDownEvent) override;
    void event(const FilApp::KeyUpEvent& keyUpEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_PICKINGCONTEXT_HPP
