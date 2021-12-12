#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{
void FlowMeshController::registerIInputEventListener(
    FilApp::InputEventListener* inputListener)
{
    m_inputEventDispatcher->registerListener(inputListener);
}
} // namespace FlowMesh
