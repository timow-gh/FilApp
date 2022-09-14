#ifndef MESHLER_FILAPPGUICONTEXT_HPP
#define MESHLER_FILAPPGUICONTEXT_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <filagui/ImGuiHelper.h>
#include <filament/View.h>
ENABLE_ALL_WARNINGS
#include <Core/Utils/Compiler.hpp>
#include <Graphics/Gui.hpp>
#include <Graphics/Viewport.hpp>
#include <memory>

namespace FilApp
{

class FilAppGuiContext : public Graphics::Gui {
public:
  FilAppGuiContext() = default;
  FilAppGuiContext(std::unique_ptr<filagui::ImGuiHelper>&& imGuiHelper, filament::View* view, filament::Renderer* renderer);

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
};

CORE_NODISCARD FilAppGuiContext createFilAppGuiContext(filament::Engine* engine, filament::Renderer* renderer, float pixelRatio);

} // namespace FilApp

#endif // MESHLER_FILAPPGUICONTEXT_HPP
