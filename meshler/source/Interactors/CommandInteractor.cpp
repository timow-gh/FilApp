#include <Graphics/InputEvents/KeyEvent.hpp>
#include <Meshler/Interactors/CommandInteractor.hpp>
#include <Meshler/MController.hpp>

namespace Meshler
{

CommandInteractor::CommandInteractor(MController& controller)
    : m_controller(&controller)
{
}

void CommandInteractor::onEvent(const Graphics::KeyEvent& keyEvent)
{
  if (auto nextInteractorCommand = m_interactorKeyMap.nextInteractor(keyEvent.keyScancode))
    m_controller->setNextInteractor(*nextInteractorCommand);
}

} // namespace Meshler
