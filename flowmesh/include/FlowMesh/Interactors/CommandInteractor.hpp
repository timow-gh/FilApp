#ifndef FILAPP_COMMANDINTERACTOR_HPP
#define FILAPP_COMMANDINTERACTOR_HPP

#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/InteractorKeyMap.hpp>
#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>

namespace FlowMesh
{

class FlowMeshController;

// Interactor that sets the currently active Interactor of the controller using the InteractorKeyMap
class CommandInteractor
    : public Interactor
    , public Graphics::InputEventListener {
    FlowMeshController* m_controller{nullptr};
    InteractorKeyMap m_interactorKeyMap{};
    Graphics::InputEventDispatcher* m_inputEventDispatcher{nullptr};

  public:
    explicit CommandInteractor(FlowMeshController* controller,
                               Graphics::InputEventDispatcher* inputEventDispatcher);

    void initListeners() override;

    CommandInteractor(CommandInteractor&& rhs) = default;
    CommandInteractor& operator=(CommandInteractor&& rhs) = default;

    ~CommandInteractor() override { m_inputEventDispatcher->removeListener(this); }

    void onEvent(const Graphics::KeyEvent& keyEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_COMMANDINTERACTOR_HPP
