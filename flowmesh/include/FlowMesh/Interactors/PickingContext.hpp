#ifndef FILAPP_PICKINGCONTEXT_HPP
#define FILAPP_PICKINGCONTEXT_HPP

#include <Core/Types/TVector.hpp>
#include <FilAppInterfaces/InputEvents/IInputEventListener.hpp>
#include <Geometry/Line.hpp>

namespace FlowMesh
{
struct PickingResult
{
    Geometry::Ray3d pickingRay;
    Core::TVector<double_t> pickingOrdinates;
};

class PickingContext : public FilApp::IInputEventListener {
    Geometry::Ray3d m_pickingRay;

  private:
    void mouseDown(const FilApp::MouseDownEvent& mouseDownEvent) override;
    void mouseUp(const FilApp::MouseUpEvent& mouseUpEvent) override;
    void mouseMove(const FilApp::MouseMoveEvent& mouseMovedEvent) override;
    void mouseWheel(const FilApp::MouseWheelEvent& mouseWheelEvent) override;
    void keyDown(const FilApp::KeyDownEvent& keyDownEvent) override;
    void keyUp(const FilApp::KeyUpEvent& keyUpEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_PICKINGCONTEXT_HPP
