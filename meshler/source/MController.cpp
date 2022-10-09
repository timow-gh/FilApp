#include <Meshler/GeometryElements/MConeTraits.hpp>
#include <Meshler/GeometryElements/MCuboidTraits.hpp>
#include <Meshler/GeometryElements/MCylinderTraits.hpp>
#include <Meshler/GeometryElements/MSphereTraits.hpp>
#include <Meshler/Interactors/CommandInteractor.hpp>
#include <Meshler/Interactors/MElementPlacingInteractor.hpp>
#include <Meshler/Interactors/MGridInteractor.hpp>
#include <Meshler/Interactors/MeshlerCommands.hpp>
#include <Meshler/MController.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/MPresenter.hpp>

namespace Meshler
{
MController::MController(MPresenter& meshlerPresenter, MModel& meshlerModel)
    : m_meshlerPresenter(meshlerPresenter)
    , m_meshlerModel(meshlerModel)
{
}
std::shared_ptr<MController> MController::create(MPresenter& meshlerPresenter, MModel& meshlerModel)
{
  auto controller = std::make_shared<MController>(meshlerPresenter, meshlerModel);
  controller->m_commandInteractor = std::make_unique<CommandInteractor>(*controller);
  meshlerPresenter.registerListener(controller.get());
  controller->setNextInteractor(MeshlerCommands::PLACING_INTERACTOR_SPHERE);

  MGrid defaultGrid = MGrid{};
  FGuid defaultGridGuid = defaultGrid.getFGuid();
  meshlerModel.add(std::move(defaultGrid));
  controller->m_meshlerGridInteractor = std::make_unique<MGridInteractor>(meshlerModel, defaultGridGuid);

  meshlerPresenter.registerRayPickEventListener(controller->m_meshlerGridInteractor.get());

  return controller;
}
void MController::onEvent(const Graphics::KeyEvent& keyEvent)
{
  m_commandInteractor->onEvent(keyEvent);
}
void MController::setNextInteractor(const MeshlerCommands& meshlerCommand)
{
  m_meshlerPresenter.get().removeListener(m_currentInteractor.get());

  switch (meshlerCommand)
  {
  case MeshlerCommands::PLACING_INTERACTOR_SPHERE:
  {
    m_currentInteractor =
        std::make_unique<MElementPlacingInteractor<MSphere, double_t, SphereTraitsConfig>>(m_meshlerModel.get(),
                                                                                           SphereTraitsConfig<double_t>{});
    break;
  }
  case MeshlerCommands::PLACING_INTERACTOR_CONE:
  {
    m_currentInteractor =
        std::make_unique<MElementPlacingInteractor<MCone, double_t, ConeTraitsConfig>>(m_meshlerModel.get(), ConeTraitsConfig<double_t>{});
    break;
  }
  case MeshlerCommands::PLACING_INTERACTOR_CYLINDER:
  {
    m_currentInteractor =
        std::make_unique<MElementPlacingInteractor<MCylinder, double_t, CylinderTraitsConfig>>(m_meshlerModel.get(),
                                                                                               CylinderTraitsConfig<double_t>{});
    break;
  }
  case MeshlerCommands::PLACING_INTERACTOR_CUBOID:
  {
    m_currentInteractor =
        std::make_unique<MElementPlacingInteractor<MCuboid, double_t, CuboidTraitsConfig>>(m_meshlerModel.get(),
                                                                                           CuboidTraitsConfig<double_t>{});
    break;
  }
  }

  m_meshlerPresenter.get().registerListener(m_currentInteractor.get());
}
void MController::onCommand(const std::uint32_t& commandId)
{
  switch (commandId)
  {
  case static_cast<std::uint32_t>(MeshlerCommands::PLACING_INTERACTOR_SPHERE):
  {
    setNextInteractor(MeshlerCommands::PLACING_INTERACTOR_SPHERE);
    return;
  }
  case static_cast<std::uint32_t>(MeshlerCommands::PLACING_INTERACTOR_CYLINDER):
  {
    setNextInteractor(MeshlerCommands::PLACING_INTERACTOR_CYLINDER);
    return;
  }
  case static_cast<std::uint32_t>(MeshlerCommands::PLACING_INTERACTOR_CUBOID):
  {
    setNextInteractor(MeshlerCommands::PLACING_INTERACTOR_CUBOID);
    return;
  }
  case static_cast<std::uint32_t>(MeshlerCommands::PLACING_INTERACTOR_CONE):
  {
    setNextInteractor(MeshlerCommands::PLACING_INTERACTOR_CONE);
    return;
  }
  default:
  {
    setNextInteractor(static_cast<MeshlerCommands>(MeshlerCommands::PLACING_INTERACTOR_SPHERE));
    return;
  }
  }
}

} // namespace Meshler