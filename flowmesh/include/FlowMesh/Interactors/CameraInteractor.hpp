#ifndef FILAPP_CAMERAINTERACTOR_HPP
#define FILAPP_CAMERAINTERACTOR_HPP

#include <FlowMesh/Interactors/Interactor.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>

namespace FlowMesh
{
class CameraInteractor
    : public Interactor
    , public Graphics::InputEventListener {
};
} // namespace FlowMesh

#endif // FILAPP_CAMERAINTERACTOR_HPP
