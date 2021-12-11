#ifndef FILAPP_PICKINGCONTEXT_HPP
#define FILAPP_PICKINGCONTEXT_HPP

#include "FilAppInterfaces/InputEvents/IInputListener.hpp"
#include <Core/Types/TVector.hpp>
#include <Geometry/Line.hpp>

namespace FlowMesh
{
struct PickingResult
{
    Geometry::Ray3d pickingRay;
    Core::TVector<double_t> pickingOrdinates;
};

class PickingContext
    : public FilApp::IInputListener
{
    Geometry::Ray3d m_pickingRay;

  public:

  private:
    void mouseDown(const FilApp::MouseDownEvent& mouseDownEvent) override;
    void mouseUp(const FilApp::MouseUpEvent& mouseUpEvent) override;
    void mouseMoved(const FilApp::MouseMovedEvent& mouseMovedEvent) override;
    void mouseWheel(const FilApp::MouseWheelEvent& mouseWheelEvent) override;
    void keyDown(const FilApp::KeyDownEvent& keyDownEvent) override;
    void keyUp(const FilApp::KeyUpEvent& keyUpEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_PICKINGCONTEXT_HPP
