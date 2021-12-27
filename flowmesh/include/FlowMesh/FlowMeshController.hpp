#ifndef FILAPP_FLOWMESHCONTROLLER_HPP
#define FILAPP_FLOWMESHCONTROLLER_HPP

#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <memory>

namespace FilApp
{
class InputEventListener;
}

namespace FlowMesh
{
class FlowMeshController {
    FilApp::InputEventDispatcher* m_inputEventDispatcher{nullptr};
    FilApp::RayPickEventDispatcher* m_rayPickDispatcher{nullptr};

    FlowMeshModel* m_model{nullptr};

    std::unique_ptr<Interactor> m_interactor{nullptr};

  public:
    FlowMeshController(FilApp::View* mainView,
                       FlowMeshModel* model,
                       std::unique_ptr<Interactor>&& interactor)
        : m_inputEventDispatcher(mainView)
        , m_rayPickDispatcher(mainView)
        , m_model(model)
        , m_interactor(std::move(interactor))
    {
        m_inputEventDispatcher->registerListener(m_interactor.get());
        m_rayPickDispatcher->registerListener(m_interactor.get());
    }

    FlowMeshController(FlowMeshController&& rhs) noexcept = default;
    FlowMeshController& operator=(FlowMeshController&& rhs) noexcept = default;
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
