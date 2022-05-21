#ifndef MESHLER_COMMANDINTERACTOR_HPP
#define MESHLER_COMMANDINTERACTOR_HPP

#include <Meshler/Interactors/InteractorKeyMap.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>

namespace Meshler
{

class MController;

// Interactor that sets the currently active Interactor of the controller using the InteractorKeyMap
class CommandInteractor : public Graphics::InputEventListener {
    MController* m_controller{nullptr};
    InteractorKeyMap m_interactorKeyMap{};

  public:
    explicit CommandInteractor(MController& controller);

    CommandInteractor(CommandInteractor&& rhs) = default;
    CommandInteractor& operator=(CommandInteractor&& rhs) = default;

    void onEvent(const Graphics::KeyEvent& keyEvent) override;
};

} // namespace Meshler

#endif // MESHLER_COMMANDINTERACTOR_HPP
