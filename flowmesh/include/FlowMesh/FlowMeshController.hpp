#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include "FilAppInterfaces/InputEvents/IInputEventDispatcher.hpp"

namespace FilApp
{
class InputEventListener;
}

namespace FlowMesh
{
class FlowMeshController
{
    FilApp::IInputEventDispatcher* m_inputEventDispatcher{nullptr};

  public:
    void registerIInputEventListener(FilApp::InputEventListener* inputListener);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
