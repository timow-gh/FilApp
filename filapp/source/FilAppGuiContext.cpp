#include "FilApp/FilAppGuiContext.hpp"
#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Viewport.h>
#include <imgui.h>
ENABLE_ALL_WARNINGS
#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/MouseMoveEvent.hpp>
#include <Graphics/InputEvents/MouseWheelEvent.hpp>
#include <utility>

namespace FilApp
{

FilAppGuiWidget::FilAppWidgetFunctor creatButton(const Graphics::Command& command)
{
  return [cmd = command]()
  {
    if (ImGui::Button(cmd.getName().c_str()))
      cmd.getCallback()(cmd.getId());
  };
}

FilAppGuiContext::FilAppGuiContext(std::unique_ptr<filagui::ImGuiHelper>&& imGuiHelper, filament::View* view, filament::Renderer* renderer)
    : m_ImGuiHelper(std::move(imGuiHelper))
    , m_renderer(renderer)
    , m_view(view)
{
  CORE_POSTCONDITION_DEBUG_ASSERT(m_ImGuiHelper, "ImGuiHelper must not be null");
  CORE_POSTCONDITION_DEBUG_ASSERT(m_renderer, "Renderer must not be null");
  CORE_POSTCONDITION_DEBUG_ASSERT(m_view, "View must not be null");
}
void FilAppGuiContext::updateUserInterface()
{
  const float width = ImGui::GetIO().DisplaySize.x;
  const float height = ImGui::GetIO().DisplaySize.y;
  ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
  ImGui::SetNextWindowSizeConstraints(ImVec2(width, height), ImVec2(width, height));
  //   Disable rounding and draw a fixed-height ImGui window that looks like a sidebar.
  ImGui::GetStyle().WindowRounding = 0;
  ImGui::SetNextWindowPos(ImVec2(0, 0));

  ImGui::Begin("FilAppGui", nullptr, ImGuiWindowFlags_MenuBar);

  //  ImGui::ShowDemoWindow();

  m_filAppGuiWidget.udpate();

  ImGui::End();
}
void FilAppGuiContext::render(double_t timeStepInSeconds)
{
  CORE_PRECONDITION_DEBUG_ASSERT(m_ImGuiHelper, "m_ImGuiHelper is null");
  if (!m_ImGuiHelper)
    return;

  m_ImGuiHelper->setDisplaySize(static_cast<int>(m_viewport.width), static_cast<int>(m_viewport.height), 1, 1);
  m_ImGuiHelper->render(static_cast<float_t>(timeStepInSeconds),
                        [this](filament::Engine*, filament::View*) { this->updateUserInterface(); });

  m_renderer->render(m_view);
}

Graphics::Viewport FilAppGuiContext::getViewport() const
{
  return m_viewport;
}

void FilAppGuiContext::setViewPort(const Graphics::Viewport& viewport)
{
  m_viewport = viewport;
  m_view->setViewport(toFilamentViewport(viewport));
}
void FilAppGuiContext::onRemoveInputEventListener()
{
  CORE_POSTCONDITION_ASSERT(false, "Not implemented");
}
void FilAppGuiContext::onEvent(const Graphics::MouseButtonEvent& event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos.x = event.x;
  io.MousePos.y = m_viewport.height - event.y;

  if (event.type == Graphics::MouseButtonEvent::Type::PUSH)
  {
    if (event.buttonIndex == 1)
      io.MouseDown[0] = true;
    else if (event.buttonIndex == 3)
      io.MouseDown[1] = true;
  }
  else if (event.type == Graphics::MouseButtonEvent::Type::RELEASE)
  {
    if (event.buttonIndex == 1)
      io.MouseDown[0] = false;
    else if (event.buttonIndex == 3)
      io.MouseDown[1] = false;
  }
}
void FilAppGuiContext::onEvent(const Graphics::MouseMoveEvent& event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos.x = event.x;
  io.MousePos.y = m_viewport.height - event.y;
}
void FilAppGuiContext::onEvent(const Graphics::MouseWheelEvent& event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheel += event.x;
}
void FilAppGuiContext::onEvent(const Graphics::KeyEvent& event)
{
  CORE_POSTCONDITION_ASSERT(false, "Not implemented");
}
void FilAppGuiContext::registerButtonCommand(const Graphics::Command& command)
{
  addFilAppWidget(FilApp::creatButton(command));
}

FilAppGuiContext
createFilAppGuiContext(filament::View* filamentView, filament::Engine* engine, filament::Renderer* renderer, float pixelRatio)
{
  CORE_PRECONDITION_DEBUG_ASSERT(filamentView, "Filament view must not be null");
  CORE_PRECONDITION_DEBUG_ASSERT(engine, "Engine must not be null");
  CORE_PRECONDITION_DEBUG_ASSERT(renderer, "Renderer must not be null");

  CORE_POSTCONDITION_ASSERT(filamentView, "Failed to create view");
  auto filAppGui = FilAppGuiContext(std::make_unique<filagui::ImGuiHelper>(engine, filamentView, ""), filamentView, renderer);

  auto guiIO = ImGui::GetIO();

  // Using ANSI codes
  guiIO.KeyMap[ImGuiKey_Tab] = 9;
  guiIO.KeyMap[ImGuiKey_LeftArrow] = 37;
  guiIO.KeyMap[ImGuiKey_RightArrow] = 39;
  guiIO.KeyMap[ImGuiKey_UpArrow] = 38;
  guiIO.KeyMap[ImGuiKey_DownArrow] = 40;
  guiIO.KeyMap[ImGuiKey_Home] = 36;
  guiIO.KeyMap[ImGuiKey_End] = 35;
  guiIO.KeyMap[ImGuiKey_Delete] = 46;
  guiIO.KeyMap[ImGuiKey_Backspace] = 8;
  guiIO.KeyMap[ImGuiKey_Enter] = 13;
  guiIO.KeyMap[ImGuiKey_Escape] = 27;
  guiIO.KeyMap[ImGuiKey_A] = 65;
  guiIO.KeyMap[ImGuiKey_C] = 67;
  guiIO.KeyMap[ImGuiKey_V] = 86;
  guiIO.KeyMap[ImGuiKey_X] = 88;
  guiIO.KeyMap[ImGuiKey_Y] = 89;
  guiIO.KeyMap[ImGuiKey_Z] = 90;

  guiIO.FontGlobalScale = pixelRatio; // High DPI support
  ImGui::GetStyle().ScaleAllSizes(pixelRatio);

  return std::move(filAppGui);
}
} // namespace FilApp
