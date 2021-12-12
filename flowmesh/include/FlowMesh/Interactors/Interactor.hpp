#ifndef FILAPP_INTERACTOR_HPP
#define FILAPP_INTERACTOR_HPP

namespace FlowMesh
{
class Interactor
    : public FilApp::InputEventListener
    , public FilApp::RayPickEventListener {
};
} // namespace FlowMesh

#endif // FILAPP_INTERACTOR_HPP
