#include "FlowMesh/Interactors/CommandInteractor.hpp"
#include "FlowMesh/Controller.hpp"

namespace FlowMesh
{

CommandInteractor::CommandInteractor(Controller* controller,
                                     Graphics::InputEventDispatcher* inputEventDispatcher)
    : m_controller(controller), m_inputEventDispatcher(inputEventDispatcher)
{
}

void CommandInteractor::event(const Graphics::KeyEvent& keyEvent)
{
    if (auto nextInteractorCommand = m_interactorKeyMap.nextInteractor(keyEvent.keyScancode))
        m_controller->setNextInteractor(*nextInteractorCommand);
}

void CommandInteractor::initListeners()
{
    m_inputEventDispatcher->registerListener(this);
}

} // namespace FlowMesh
