#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include "FilAppInterfaces/InputEvents/IInputEventDispatcher.hpp"

namespace FilApp
{
class IInputEventListener;
}

namespace FlowMesh
{
class FlowMeshController
{
    FilApp::IInputEventDispatcher* m_inputEventDispatcher{nullptr};

  public:
    void registerIInputEventListener(FilApp::IInputEventListener* inputListener);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
