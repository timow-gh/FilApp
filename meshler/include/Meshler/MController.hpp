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

namespace Meshler
{

class MController : public Graphics::GraphicsController {
    MPresenter* m_meshlerPresenter{nullptr};
    MModel* m_meshlerModel{nullptr};

    std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
    std::unique_ptr<MGridInteractor> m_meshlerGridInteractor{nullptr};
    std::unique_ptr<Graphics::GraphicsController> m_currentInteractor{nullptr};

  public:
    MController() = default;

    CORE_NODISCARD static std::shared_ptr<MController>
    create(MPresenter* meshlerPresenter,
                                                              MModel* meshlerModel)
    {
        auto controller = std::make_shared<MController>(MController(meshlerPresenter, meshlerModel));
        controller->m_commandInteractor = std::make_unique<CommandInteractor>(*controller);
        meshlerPresenter->registerListener(controller.get());
        controller->setNextInteractor(InteractorCommand(Command::PLACING_INTERACTOR_SPHERE));

        controller->m_meshlerGridInteractor = MGridInteractor::create(*meshlerModel, MGrid{});
        meshlerPresenter->registerRayPickEventListener(controller->m_meshlerGridInteractor.get());

        return controller;
    }

    void onEvent(const Graphics::KeyEvent& keyEvent) override
    {
        m_commandInteractor->onEvent(keyEvent);
    }

    void setNextInteractor(const InteractorCommand& command)
    {
        m_meshlerPresenter->removeListener(m_currentInteractor.get());

        switch (command.getId())
        {
        case Command::PLACING_INTERACTOR_SPHERE:
        {
            m_currentInteractor =
                std::make_unique<MElementPlacingInteractor<MSphere, double_t, SphereTraitsConfig>>(
                    *m_meshlerModel,
                    SphereTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CONE:
        {
            m_currentInteractor =
                std::make_unique<MElementPlacingInteractor<MCone, double_t, ConeTraitsConfig>>(
                    *m_meshlerModel,
                    ConeTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CYLINDER:
        {
            m_currentInteractor = std::make_unique<
                MElementPlacingInteractor<MCylinder, double_t, CylinderTraitsConfig>>(
                *m_meshlerModel,
                CylinderTraitsConfig<double_t>{});
            break;
        }
        case Command::PLACING_INTERACTOR_CUBOID:
        {
            m_currentInteractor =
                std::make_unique<MElementPlacingInteractor<MCuboid, double_t, CuboidTraitsConfig>>(
                    *m_meshlerModel,
                    CuboidTraitsConfig<double_t>{});
            break;
        }
        }

        m_meshlerPresenter->registerListener(m_currentInteractor.get());
    }

  private:
    MController(MPresenter* meshlerPresenter, MModel* meshlerModel)
        : m_meshlerPresenter(meshlerPresenter), m_meshlerModel(meshlerModel)
    {
    }
};

} // namespace Meshler

#endif // MESHLER_MCONTROLLER_HPP
