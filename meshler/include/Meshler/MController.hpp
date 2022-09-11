#ifndef MESHLER_MCONTROLLER_HPP
#define MESHLER_MCONTROLLER_HPP

#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <functional>
#include <memory>

namespace Meshler
{

class MPresenter;
class MModel;
class CommandInteractor;
class MGridInteractor;
class InteractorCommand;

class MController : public Graphics::GraphicsController {
  std::reference_wrapper<MPresenter> m_meshlerPresenter;
  std::reference_wrapper<MModel> m_meshlerModel;

  std::unique_ptr<CommandInteractor> m_commandInteractor{nullptr};
  std::unique_ptr<MGridInteractor> m_meshlerGridInteractor{nullptr};
  std::unique_ptr<Graphics::GraphicsController> m_currentInteractor{nullptr};

public:
  MController(MPresenter& meshlerPresenter, MModel& meshlerModel);

  CORE_NODISCARD static std::shared_ptr<MController> create(MPresenter& meshlerPresenter, MModel& meshlerModel);

  void onEvent(const Graphics::KeyEvent& keyEvent) override;
  void setNextInteractor(const InteractorCommand& command);
};

} // namespace Meshler

#endif // MESHLER_MCONTROLLER_HPP
