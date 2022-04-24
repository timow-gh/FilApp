#include <FilApp/FilApplication.hpp>
#include <GraphicsInterface/Renderables/PointRenderable.hpp>
#include <GraphicsInterface/Vertex.hpp>
#include <GraphicsInterface/View.hpp>
#include <GraphicsInterface/Window.hpp>
#include <vector>

using namespace Graphics;

int main()
{
    AppConfig appConfig;
    appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;

    std::shared_ptr<Graphics::GraphicsApp> graphicsApp =
        FilApplication::getFilApp(appConfig, WindowConfig());

    Window& mainWindow = graphicsApp->getWindow();
    View* mainView = mainWindow.getMainIView();

    std::uint32_t hexColor = 0xFFc0bfbb;
    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, hexColor},
        Vertex{{1, 0, 0}, hexColor},
        Vertex{{0, 0, 2}, hexColor},
    };

    constexpr float_t POINT_SIZE = 15;
    mainView->addRenderable(
        PointRenderable::create(std::move(vertices), {POINT_SIZE, POINT_SIZE, POINT_SIZE}));
    mainView->addRenderable(PointRenderable::create(Vertex{{2, 0, 0}, hexColor}, POINT_SIZE));

    graphicsApp->run();

    return 0;
}