#ifndef FILAPP_CONTROLLER_HPP
#define FILAPP_CONTROLLER_HPP

#include <FlowMesh/Interactors/CameraInteractor.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/InteractorCommands.hpp>
#include <FlowMesh/Interactors/PlacingInteractor.hpp>
#include <FlowMesh/Model.hpp>
#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <memory>

namespace Graphics
{
class InputEventListener;
}

namespace FlowMesh
{

class Controller {
    Graphics::InputEventDispatcher* m_inputEventDispatcher{nullptr};
    Graphics::RayPickEventDispatcher* m_rayPickDispatcher{nullptr};

    Model* m_model{nullptr};

    std::unique_ptr<CameraInteractor> m_cameraInteractor{nullptr};
    std::unique_ptr<Interactor> m_currentInteractor{nullptr};
    std::unique_ptr<Interactor> m_nextInteractor{nullptr};

  public:
    Controller(Graphics::InputEventDispatcher& inputEventDispatcher,
               Graphics::RayPickEventDispatcher& rayPickDispatcher,
               Model* model)
        : m_inputEventDispatcher(&inputEventDispatcher)
        , m_rayPickDispatcher(&rayPickDispatcher)
        , m_model(model)
        , m_currentInteractor(std::make_unique<PlacingInteractor>(model))
    {
    }

    Controller(Controller&& rhs) CORE_NOEXCEPT = default;
    Controller& operator=(Controller&& rhs) CORE_NOEXCEPT = default;

    CORE_NODISCARD Graphics::InputEventDispatcher* getInputEventDispatcher() const
    {
        return m_inputEventDispatcher;
    }

    CORE_NODISCARD Graphics::RayPickEventDispatcher* getRayPickDispatcher() const
    {
        return m_rayPickDispatcher;
    }

    void onInteractorCommand(const InteractorCommand& command)
    {
        switch (command.getId())
        {
        case Commands::PLACING_INTERACTOR:
        {
            m_currentInteractor = std::make_unique<PlacingInteractor>(m_model);
            break;
        }
        }
    }
};

} // namespace FlowMesh

#endif // FILAPP_CONTROLLER_HPP
