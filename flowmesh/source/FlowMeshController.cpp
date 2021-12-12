#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{
void FlowMeshController::registerIInputEventListener(
    FilApp::InputEventListener* inputListener)
{
    m_inputEventDispatcher->registerInputListener(inputListener);
}
} // namespace FlowMesh
