#ifndef FILAPP_CONTROLLER_HPP
#define FILAPP_CONTROLLER_HPP

#include <FlowMesh/GeometryElements/FlowMeshConeTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphereTraits.hpp>
#include <FlowMesh/Interactors/CommandInteractor.hpp>
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

    std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
    std::unique_ptr<Interactor> m_currentInteractor{nullptr};

  public:
    Controller(Graphics::InputEventDispatcher& inputEventDispatcher,
               Graphics::RayPickEventDispatcher& rayPickDispatcher,
               Model* model)
        : m_inputEventDispatcher(&inputEventDispatcher)
        , m_rayPickDispatcher(&rayPickDispatcher)
        , m_model(model)
    {
    }

    void init()
    {
        m_commandInteractor = std::make_unique<CommandInteractor>(this, m_inputEventDispatcher);
        m_inputEventDispatcher->registerListener(m_commandInteractor.get());
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

    void setNextInteractor(const InteractorCommand& command)
    {
        switch (command.getId())
        {
        case Command::PLACING_INTERACTOR_SPHERE:
        {
            SphereTraitsConfig<double_t> sphereTraitsConfig;
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshSphere, double_t, SphereTraitsConfig>>(
                    m_model,
                    m_model->calcModelSnapGeometries(),
                    sphereTraitsConfig,
                    m_rayPickDispatcher);
            break;
        }
        case Command::PLACING_INTERACTOR_CONE:
        {
            ConeTraitsConfig<double_t> coneTraitsConfig;
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshCone, double_t, ConeTraitsConfig>>(
                    m_model,
                    m_model->calcModelSnapGeometries(),
                    coneTraitsConfig,
                    m_rayPickDispatcher);
        }
        }

        m_currentInteractor->initListeners();
    }
};

} // namespace FlowMesh

#endif // FILAPP_CONTROLLER_HPP
