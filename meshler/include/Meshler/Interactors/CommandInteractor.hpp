#ifndef MESHLER_COMMANDINTERACTOR_HPP
#define MESHLER_COMMANDINTERACTOR_HPP

#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Meshler/Interactors/MeshlerCommandsKeyMap.hpp>

namespace Meshler
{

class MController;

// Interactor that sets the currently active Interactor of the controller using the InteractorKeyMap
class CommandInteractor : public Graphics::InputEventListener {
  MController* m_controller{nullptr};
  MeshlerCommandsKeyMap m_interactorKeyMap{};

public:
  explicit CommandInteractor(MController& controller);

  void onEvent(const Graphics::KeyEvent& keyEvent) override;
};

} // namespace Meshler

#endif // MESHLER_COMMANDINTERACTOR_HPP
