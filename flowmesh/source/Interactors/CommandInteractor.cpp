#include "FlowMesh/Interactors/CommandInteractor.hpp"
#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{

CommandInteractor::CommandInteractor(FlowMeshController& controller,
                                     Graphics::InputEventDispatcher& inputEventDispatcher)
    : m_controller(&controller), m_inputEventDispatcher(&inputEventDispatcher)
{
}

void CommandInteractor::onEvent(const Graphics::KeyEvent& keyEvent)
{
    if (auto nextInteractorCommand = m_interactorKeyMap.nextInteractor(keyEvent.keyScancode))
        m_controller->setNextInteractor(*nextInteractorCommand);
}

void CommandInteractor::initListeners()
{
    m_inputEventDispatcher->registerListener(this);
}

} // namespace FlowMesh
