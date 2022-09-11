#include <FilApp/FilApplication.hpp>
#include <Graphics/Renderables/LineRenderable.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/View.hpp>
#include <Graphics/Window.hpp>

using namespace Graphics;

int main()
{
  AppConfig appConfig;
  appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;

  std::shared_ptr<Graphics::GraphicsApp> graphicsApp = FilApp::FilApplication::getFilApp(appConfig, WindowConfig());

  Window& mainWindow = graphicsApp->getWindow();
  View* mainView = mainWindow.getMainIView();

  std::uint32_t hexColor = 0xFFc0bfbb;
  mainView->addRenderable(LineRenderable::create(Vertex{{0, 0, 0}, hexColor}, Vertex{{1, 0, 0}, hexColor}));

  std::vector<Vertex> vertices = {Vertex{{0, 0, 0}, hexColor},
                                  Vertex{{0, 2, 0}, hexColor},
                                  Vertex{{0, 0, 0}, hexColor},
                                  Vertex{{0, 0, 3}, hexColor}};
  mainView->addRenderable(LineRenderable::create(std::move(vertices)));

  graphicsApp->run();

  return 0;
}