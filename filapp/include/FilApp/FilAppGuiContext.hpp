#ifndef MESHLER_FILAPPGUICONTEXT_HPP
#define MESHLER_FILAPPGUICONTEXT_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <filagui/ImGuiHelper.h>
#include <filament/View.h>
ENABLE_ALL_WARNINGS
#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Graphics/Gui.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/Viewport.hpp>
#include <memory>

namespace FilApp
{

class FilAppGuiWidget {
public:
  // The Callbacks hold everything needed to build Imgui widgets and their callbacks.
  // Invoking the FilAppWidgetCallback rebuilds the Imgui widgets and is only triggered from Imgui itself.
  using FilAppWidgetFunctor = std::function<void()>;

private:
  Core::TVector<FilAppWidgetFunctor> m_filAppWidgetCallables;

public:
  void addWidget(FilAppWidgetFunctor&& filAppWidgetCallable) { m_filAppWidgetCallables.push_back(std::move(filAppWidgetCallable)); }
  void invoke() const
  {
    for (const auto& filAppWidgetCallable: m_filAppWidgetCallables)
      filAppWidgetCallable();
  }
};

class FilAppGuiContext
    : public Graphics::Gui
    , public Graphics::InputEventListener {
public:
  FilAppGuiContext() = default;
  FilAppGuiContext(std::unique_ptr<filagui::ImGuiHelper>&& imGuiHelper, filament::View* view, filament::Renderer* renderer);

  FilAppGuiContext(const FilAppGuiContext&) = delete;
  FilAppGuiContext& operator=(const FilAppGuiContext&) = delete;

  FilAppGuiContext(FilAppGuiContext&&) = default;
  FilAppGuiContext& operator=(FilAppGuiContext&&) = default;
  ~FilAppGuiContext() override = default;

  void onRemoveInputEventListener() override;
  void onEvent(const Graphics::MouseButtonEvent& event) override;
  void onEvent(const Graphics::MouseMoveEvent& event) override;
  void onEvent(const Graphics::MouseWheelEvent& event) override;
  void onEvent(const Graphics::KeyEvent& event) override;

  CORE_NODISCARD Graphics::Viewport getViewport() const;
  void setViewPort(const Graphics::Viewport& viewport);

  void render(double_t timeStepInSeconds) override;

  CORE_NODISCARD filament::View* getView() const { return m_view; }

private:
  void updateUserInterface() override;

  Graphics::Viewport m_viewport;
  filament::Renderer* m_renderer{nullptr};
  filament::View* m_view{nullptr};
  std::unique_ptr<filagui::ImGuiHelper> m_ImGuiHelper;
  bool m_postProcessingEnabled{false};
  FilAppGuiWidget m_filAppGuiWidget;
};

CORE_NODISCARD FilAppGuiContext createFilAppGuiContext(filament::View* filamentView,
                                                       filament::Engine* engine,
                                                       filament::Renderer* renderer,
                                                       float pixelRatio);

} // namespace FilApp

#endif // MESHLER_FILAPPGUICONTEXT_HPP
