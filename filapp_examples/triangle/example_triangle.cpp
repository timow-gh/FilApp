#include <FilApp/FilApplication.hpp>
#include <GraphicsInterface/View.hpp>

using namespace Graphics;

int main()
{
    AppConfig appConfig;
    appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;

    std::shared_ptr<Graphics::GraphicsApp> graphicsApp =
        FilApplication::getFilApp(appConfig, WindowConfig());

    Window& mainWindow = graphicsApp->getWindow();
    View* mainView = mainWindow.getMainIView();

    mainView->addRenderable(TriangleRenderable(
        {
            Vertex{{0, 0, 0}, 0xffff0000u},
            Vertex{{1, 0, 0}, 0xff00ff00u},
            Vertex{{0, 0, 2}, 0xff0000ffu},
        },
        {0, 1, 2}));

    graphicsApp->run();

    return 0;
}
