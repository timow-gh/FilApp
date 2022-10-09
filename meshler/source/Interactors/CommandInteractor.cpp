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
  m_controller->setNextInteractor(m_interactorKeyMap.nextInteractor(keyEvent.keyScancode));
}

} // namespace Meshler
