#ifndef FILAPP_COMMANDINTERACTOR_HPP
#define FILAPP_COMMANDINTERACTOR_HPP

#include <FlowMesh/Interactors/InteractorKeyMap.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>

namespace FlowMesh
{

class FlowMeshController;

// Interactor that sets the currently active Interactor of the controller using the InteractorKeyMap
class CommandInteractor : public Graphics::InputEventListener {
    FlowMeshController* m_controller{nullptr};
    InteractorKeyMap m_interactorKeyMap{};

  public:
    explicit CommandInteractor(FlowMeshController& controller);

    CommandInteractor(CommandInteractor&& rhs) = default;
    CommandInteractor& operator=(CommandInteractor&& rhs) = default;

    void onEvent(const Graphics::KeyEvent& keyEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_COMMANDINTERACTOR_HPP
