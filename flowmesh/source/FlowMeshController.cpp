#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{
void FlowMeshController::registerIInputEventListener(
    FilApp::IInputEventListener* inputListener)
{
    m_inputEventDispatcher->registerInputListener(inputListener);
}
} // namespace FlowMesh
