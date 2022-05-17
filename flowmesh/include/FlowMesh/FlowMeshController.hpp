#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/GeometryElements/FlowMeshConeTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboidTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinderTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphereTraits.hpp>
#include <FlowMesh/Interactors/CommandInteractor.hpp>
#include <FlowMesh/Interactors/FlowMeshGridInteractor.hpp>
#include <FlowMesh/Interactors/InteractorCommands.hpp>
#include <FlowMesh/Interactors/PlacingInteractor.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <memory>

namespace FlowMesh
{

class FlowMeshController : public Graphics::GraphicsController {
    FlowMeshPresenter* m_flowMeshPresenter{nullptr};
    FlowMeshModel* m_flowMeshModel{nullptr};

    std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
    std::unique_ptr<FlowMeshGridInteractor> m_flowMeshGridInteractor{nullptr};
    std::unique_ptr<Graphics::GraphicsController> m_currentInteractor{nullptr};

  public:
    FlowMeshController() = default;

    CORE_NODISCARD static std::shared_ptr<FlowMeshController>
    create(FlowMeshPresenter* flowMeshPresenter, FlowMeshModel* flowMeshModel)
    {
        auto controller = std::make_shared<FlowMeshController>(
            FlowMeshController(flowMeshPresenter, flowMeshModel));
        controller->m_commandInteractor = std::make_unique<CommandInteractor>(*controller);
        flowMeshPresenter->registerListener(controller.get());
        controller->setNextInteractor(InteractorCommand(Command::PLACING_INTERACTOR_SPHERE));

        controller->m_flowMeshGridInteractor =
            FlowMeshGridInteractor::create(*flowMeshModel, FlowMeshGrid{});
        flowMeshPresenter->registerRayPickEventListener(controller->m_flowMeshGridInteractor.get());

        return controller;
    }

    void onEvent(const Graphics::KeyEvent& keyEvent) override
    {
        m_commandInteractor->onEvent(keyEvent);
    }

    void setNextInteractor(const InteractorCommand& command)
    {
        m_flowMeshPresenter->removeListener(m_currentInteractor.get());

        switch (command.getId())
        {
        case Command::PLACING_INTERACTOR_SPHERE:
        {
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshSphere, double_t, SphereTraitsConfig>>(
                    *m_flowMeshModel,
                    SphereTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CONE:
        {
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshCone, double_t, ConeTraitsConfig>>(
                    *m_flowMeshModel,
                    ConeTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CYLINDER:
        {
            m_currentInteractor = std::make_unique<
                PlacingInteractor<FlowMeshCylinder, double_t, CylinderTraitsConfig>>(
                *m_flowMeshModel,
                CylinderTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CUBOID:
        {
            m_currentInteractor =
                std::make_unique<PlacingInteractor<FlowMeshCuboid, double_t, CuboidTraitsConfig>>(
                    *m_flowMeshModel,
                    CuboidTraitsConfig<double_t>{});
            break;
        }
        }

        m_flowMeshPresenter->registerListener(m_currentInteractor.get());
    }

  private:
    FlowMeshController(FlowMeshPresenter* flowMeshPresenter, FlowMeshModel* flowMeshModel)
        : m_flowMeshPresenter(flowMeshPresenter), m_flowMeshModel(flowMeshModel)
    {
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
