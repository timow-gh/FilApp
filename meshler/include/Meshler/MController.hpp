#ifndef MESHLER_MCONTROLLER_HPP
#define MESHLER_MCONTROLLER_HPP

#include <Graphics/GraphicsCommandListener.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/Window.hpp>
#include <Meshler/Interactors/Interactor.hpp>
#include <Meshler/Interactors/MeshlerCommands.hpp>
#include <functional>
#include <memory>

namespace Meshler
{

class MPresenter;
class MModel;
class CommandInteractor;
class MGridInteractor;

class MController
    : public Graphics::InputEventListener
    , public Graphics::GraphicsCommandListener {
  std::reference_wrapper<Graphics::InputEventDispatcher> m_inputEventDispatcher;
  std::reference_wrapper<Graphics::RayPickEventDispatcher> m_rayPickEventDispatcher;

  std::reference_wrapper<MPresenter> m_meshlerPresenter;
  std::reference_wrapper<MModel> m_meshlerModel;

  std::unique_ptr<CommandInteractor> m_commandInteractor;
  std::unique_ptr<MGridInteractor> m_meshlerGridInteractor;
  std::unique_ptr<Interactor> m_currentInteractor;

public:
  MController(MPresenter& meshlerPresenter,
              MModel& meshlerModel,
              Graphics::InputEventDispatcher& inputEventDispatcher,
              Graphics::RayPickEventDispatcher& rayPickEventDispatcher);

  CORE_NODISCARD static std::shared_ptr<MController> create(MPresenter& meshlerPresenter,
                                                            MModel& meshlerModel,
                                                            Graphics::Window& window,
                                                            Graphics::InputEventDispatcher& inputEventDispatcher);

  void onEvent(const Graphics::KeyEvent& keyEvent) override;
  void setNextInteractor(const MeshlerCommands& meshlerCommand);

  void onCommand(const Graphics::CommandId& commandId) override;
};

} // namespace Meshler

#endif // MESHLER_MCONTROLLER_HPP
