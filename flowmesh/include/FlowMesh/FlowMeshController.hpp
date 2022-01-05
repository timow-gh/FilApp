#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/CameraInteractor.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/PlacingInteractor.hpp>
#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <memory>

namespace Graphics
{
class InputEventListener;
}

namespace FlowMesh
{
class FlowMeshController {
    Graphics::InputEventDispatcher* m_inputEventDispatcher{nullptr};
    Graphics::RayPickEventDispatcher* m_rayPickDispatcher{nullptr};

    FlowMeshModel* m_model{nullptr};

    std::unique_ptr<CameraInteractor> m_cameraInteractor{nullptr};
    std::unique_ptr<Interactor> m_interactor{nullptr};

  public:
    FlowMeshController(Graphics::InputEventDispatcher& inputEventDispatcher,
                       Graphics::RayPickEventDispatcher& rayPickDispatcher,
                       FlowMeshModel* model)
        : m_inputEventDispatcher(&inputEventDispatcher)
        , m_rayPickDispatcher(&rayPickDispatcher)
        , m_model(model)
        , m_interactor(std::make_unique<PlacingInteractor>(model))
    {
    }
    FlowMeshController(FlowMeshController&& rhs) CORE_NOEXCEPT = default;
    FlowMeshController& operator=(FlowMeshController&& rhs) CORE_NOEXCEPT = default;

    CORE_NODISCARD Graphics::InputEventDispatcher* getInputEventDispatcher() const
    {
        return m_inputEventDispatcher;
    }

    CORE_NODISCARD Graphics::RayPickEventDispatcher* getRayPickDispatcher() const
    {
        return m_rayPickDispatcher;
    }
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
