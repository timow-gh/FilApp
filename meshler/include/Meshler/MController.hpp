#ifndef MESHLER_MCONTROLLER_HPP
#define MESHLER_MCONTROLLER_HPP

#include <Meshler/MModel.hpp>
#include <Meshler/GeometryElements/MConeTraits.hpp>
#include <Meshler/GeometryElements/MCuboidTraits.hpp>
#include <Meshler/GeometryElements/MCylinderTraits.hpp>
#include <Meshler/GeometryElements/MSphereTraits.hpp>
#include <Meshler/Interactors/CommandInteractor.hpp>
#include <Meshler/Interactors/MGridInteractor.hpp>
#include <Meshler/Interactors/InteractorCommands.hpp>
#include <Meshler/Interactors/MElementPlacingInteractor.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <memory>

namespace FlowMesh
{

class MController : public Graphics::GraphicsController {
    MPresenter* m_flowMeshPresenter{nullptr};
    MModel* m_flowMeshModel{nullptr};

    std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
    std::unique_ptr<MGridInteractor> m_flowMeshGridInteractor{nullptr};
    std::unique_ptr<Graphics::GraphicsController> m_currentInteractor{nullptr};

  public:
    MController() = default;

    CORE_NODISCARD static std::shared_ptr<MController>
    create(MPresenter* flowMeshPresenter,
                                                              MModel* flowMeshModel)
    {
        auto controller = std::make_shared<MController>(MController(flowMeshPresenter, flowMeshModel));
        controller->m_commandInteractor = std::make_unique<CommandInteractor>(*controller);
        flowMeshPresenter->registerListener(controller.get());
        controller->setNextInteractor(InteractorCommand(Command::PLACING_INTERACTOR_SPHERE));

        controller->m_flowMeshGridInteractor = MGridInteractor::create(*flowMeshModel, MGrid{});
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
                std::make_unique<MElementPlacingInteractor<MSphere, double_t, SphereTraitsConfig>>(
                    *m_flowMeshModel,
                    SphereTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CONE:
        {
            m_currentInteractor =
                std::make_unique<MElementPlacingInteractor<MCone, double_t, ConeTraitsConfig>>(
                    *m_flowMeshModel,
                    ConeTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CYLINDER:
        {
            m_currentInteractor = std::make_unique<
                MElementPlacingInteractor<MCylinder, double_t, CylinderTraitsConfig>>(
                *m_flowMeshModel,
                CylinderTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CUBOID:
        {
            m_currentInteractor =
                std::make_unique<MElementPlacingInteractor<MCuboid, double_t, CuboidTraitsConfig>>(
                    *m_flowMeshModel,
                    CuboidTraitsConfig<double_t>{});
            break;
        }
        }

        m_flowMeshPresenter->registerListener(m_currentInteractor.get());
    }

  private:
    MController(MPresenter* flowMeshPresenter, MModel* flowMeshModel)
        : m_flowMeshPresenter(flowMeshPresenter), m_flowMeshModel(flowMeshModel)
    {
    }
};

} // namespace FlowMesh

#endif // MESHLER_MCONTROLLER_HPP
