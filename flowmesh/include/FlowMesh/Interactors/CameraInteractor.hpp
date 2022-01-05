#ifndef FILAPP_CAMERAINTERACTOR_HPP
#define FILAPP_CAMERAINTERACTOR_HPP

#include "GraphicsInterface/InputEvents/InputEventListener.hpp"
#include "Interactor.hpp"

namespace FlowMesh
{
class CameraInteractor
    : public Interactor
    , public Graphics::InputEventListener {
};
} // namespace FlowMesh

#endif // FILAPP_CAMERAINTERACTOR_HPP
