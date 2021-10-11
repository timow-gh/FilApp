#include "FlowMesh/FlowMeshController.hpp"

namespace FlowMesh
{
void FlowMeshController::registerIInputEventListener(
    FilApp::IInputListener* inputListener)
{
    m_inputEventDispatcher->registerInputListener(inputListener);
}
} // namespace FlowMesh
