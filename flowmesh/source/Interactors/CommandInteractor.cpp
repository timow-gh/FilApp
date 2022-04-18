#include "FlowMesh/Interactors/CommandInteractor.hpp"
#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{

CommandInteractor::CommandInteractor(FlowMeshController& controller) : m_controller(&controller)
{
}

void CommandInteractor::onEvent(const Graphics::KeyEvent& keyEvent)
{
    if (auto nextInteractorCommand = m_interactorKeyMap.nextInteractor(keyEvent.keyScancode))
        m_controller->setNextInteractor(*nextInteractorCommand);
}

} // namespace FlowMesh
