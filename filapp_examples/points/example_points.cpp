#include <FilApp/FilApplication.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/View.hpp>
#include <Graphics/Window.hpp>
#include <vector>

using namespace Graphics;

int main()
{
    AppConfig appConfig;
    appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;

    std::shared_ptr<Graphics::GraphicsApp> graphicsApp =
        FilApp::FilApplication::getFilApp(appConfig, WindowConfig());

    Window& mainWindow = graphicsApp->getWindow();
    View* mainView = mainWindow.getMainIView();

    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, 0xffff0000},
        Vertex{{1, 0, 0}, 0xff00ff00},
        Vertex{{0, 0, 2}, 0xff0000ff},
    };

    constexpr float_t POINT_SIZE = 15;
    mainView->addRenderable(
        PointRenderable::create(std::move(vertices), {POINT_SIZE, POINT_SIZE, POINT_SIZE}));
    mainView->addRenderable(PointRenderable::create(Vertex{{2, 0, 0}, 0xff000000}, POINT_SIZE));

    graphicsApp->run();

    return 0;
}