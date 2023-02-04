#include "FilApp/FilAppGuiContext.hpp"
#include <Core/Utils/Warnings.hpp>
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
static void ShowExampleMenuFile()
{
  ImGui::MenuItem("(demo menu)", NULL, false, false);
  if (ImGui::MenuItem("New")) {}
  if (ImGui::MenuItem("Open", "Ctrl+O")) {}
  if (ImGui::BeginMenu("Open Recent"))
  {
    ImGui::MenuItem("fish_hat.c");
    ImGui::MenuItem("fish_hat.inl");
    ImGui::MenuItem("fish_hat.h");
    if (ImGui::BeginMenu("More.."))
    {
      ImGui::MenuItem("Hello");
      ImGui::MenuItem("Sailor");
      if (ImGui::BeginMenu("Recurse.."))
      {
        ShowExampleMenuFile();
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenu();
  }
  if (ImGui::MenuItem("Save", "Ctrl+S")) {}
  if (ImGui::MenuItem("Save As..")) {}

  ImGui::Separator();
  if (ImGui::BeginMenu("Options"))
  {
    static bool enabled = true;
    ImGui::MenuItem("Enabled", "", &enabled);
    ImGui::BeginChild("child", ImVec2(0, 60), true);
    for (int i = 0; i < 10; i++)
      ImGui::Text("Scrolling Text %d", i);
    ImGui::EndChild();
    static float f = 0.5f;
    static int n = 0;
    ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
    ImGui::InputFloat("Input", &f, 0.1f);
    ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Colors"))
  {
    float sz = ImGui::GetTextLineHeight();
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
      const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
      ImVec2 p = ImGui::GetCursorScreenPos();
      ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
      ImGui::Dummy(ImVec2(sz, sz));
      ImGui::SameLine();
      ImGui::MenuItem(name);
    }
    ImGui::EndMenu();
  }

  // Here we demonstrate appending again to the "Options" menu (which we already created above)
  // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
  // In a real code-base using it would make senses to use this feature from very different code locations.
  if (ImGui::BeginMenu("Options")) // <-- Append!
  {
    static bool b = true;
    ImGui::Checkbox("SomeOption", &b);
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Disabled", false)) // Disabled
  {
    IM_ASSERT(0);
  }
  if (ImGui::MenuItem("Checked", NULL, true)) {}
  if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}
static FilAppGuiWidget::FilAppWidgetFunctor createMainMenu()
{
  return []()
  {
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        ShowExampleMenuFile();
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  };
}
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
  //  ImGui::ShowDemoWindow();

  const float width = ImGui::GetIO().DisplaySize.x;
  const float height = ImGui::GetIO().DisplaySize.y;

  createMainMenu()();

  float verticalSpace = 16;
  ImGui::SetNextWindowSize(ImVec2(width, height - verticalSpace), ImGuiCond_Once);
  ImGui::SetNextWindowSizeConstraints(ImVec2(width, height), ImVec2(width, height));
  ImGui::GetStyle().WindowRounding = 0;
  ImGui::SetNextWindowPos(ImVec2(0, verticalSpace));
  ImGui::SetNextWindowCollapsed(false);
  ImGui::Begin("Main",
               nullptr,
               ImGuiWindowFlags_NoTitleBar );
  if (ImGui::CollapsingHeader("Place Objects"))
  {
    auto placementCommandWidget = createPlacementCommandWidget(m_placementButtonCommands);
    placementCommandWidget.update();
  }
  ImGui::End();
}
FilAppGuiWidget FilAppGuiContext::createPlacementCommandWidget(const Core::TVector<Graphics::Command>& placementCommands)
{
  FilAppGuiWidget widget;

  for (std::size_t i = 0; i < placementCommands.size(); ++i)
  {
    widget.addWidget(creatButton(placementCommands[i]));
    if (i < placementCommands.size() - 1)
      widget.addWidget([]() { ImGui::SameLine(); });
  }

  return widget;
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
void FilAppGuiContext::registerPlacementButtonCommand(const Graphics::Command& command)
{
  m_placementButtonCommands.push_back(command);
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
