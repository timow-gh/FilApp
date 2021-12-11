#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include "FilAppInterfaces/InputEvents/IInputEventDispatcher.hpp"

namespace FilApp
{
class IInputListener;
}

namespace FlowMesh
{
class FlowMeshController
{
    FilApp::IInputEventDispatcher* m_inputEventDispatcher{nullptr};

  public:
    void registerIInputEventListener(FilApp::IInputListener* inputListener);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
