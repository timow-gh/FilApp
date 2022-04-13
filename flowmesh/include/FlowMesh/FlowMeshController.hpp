#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/GeometryElements/FlowMeshConeTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinderTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphereTraits.hpp>
#include <FlowMesh/Interactors/CommandInteractor.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/InteractorCommands.hpp>
#include <FlowMesh/Interactors/PlacingInteractor.hpp>
#include <GraphicsInterface/Controller.hpp>
#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <memory>

namespace FlowMesh
{

class FlowMeshController : public Graphics::Controller {
    Graphics::View* m_view{nullptr};
    FlowMeshModel* m_flowMeshModel{nullptr};

    Graphics::InputEventDispatcher* m_inputEventDispatcher{nullptr};
    Graphics::RayPickEventDispatcher* m_rayPickDispatcher{nullptr};

    std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
    std::unique_ptr<Interactor> m_currentInteractor{nullptr};

  public:
    FlowMeshController(Graphics::View* view, FlowMeshModel* flowMeshModel)
        : m_view(view)
        , m_flowMeshModel(flowMeshModel)
        , m_inputEventDispatcher(&view->getInputEventDispatcher())
        , m_rayPickDispatcher(&view->getRayPickEventDispatcher())
    {
    }

    void init()
    {
        m_commandInteractor = std::make_unique<CommandInteractor>(this, m_inputEventDispatcher);
        m_inputEventDispatcher->registerListener(m_commandInteractor.get());
    }

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
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshSphere, double_t, SphereTraitsConfig>>(
                    m_flowMeshModel,
                    m_flowMeshModel->calcModelSnapGeometries(),
                    SphereTraitsConfig<double_t>{},
                    m_rayPickDispatcher);
            break;
        }
        case Command::PLACING_INTERACTOR_CONE:
        {
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshCone, double_t, ConeTraitsConfig>>(
                    m_flowMeshModel,
                    m_flowMeshModel->calcModelSnapGeometries(),
                    ConeTraitsConfig<double_t>{},
                    m_rayPickDispatcher);

            break;
        }
        case Command::PLACING_INTERACTOR_CYLINDER:
        {
            m_currentInteractor = std::make_unique<
                PlacingInteractor<FlowMeshCylinder, double_t, CylinderTraitsConfig>>(
                m_flowMeshModel,
                m_flowMeshModel->calcModelSnapGeometries(),
                CylinderTraitsConfig<double_t>{},
                m_rayPickDispatcher);

            break;
        }
        }

        m_currentInteractor->initListeners();
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
