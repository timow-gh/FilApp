#include "FilApp/Application.hpp"
#include "FilApp/Renderable.hpp"
#include "FilApp/Vertex.hpp"
#include "FilApp/Window.hpp"

using namespace FilApp;

int main()
{
    auto windowConfig = WindowConfig();
    Application::init(AppConfig(), windowConfig);

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainIView();
    // TODO Push down use of filament
    window->getMainFilAppView()->getFilamentView()->setPostProcessingEnabled(false);

    mainView->addRenderable(Renderable(
        {
            Vertex{{0, 0, 0}, 0xffff0000u},
            Vertex{{1, 0, 0}, 0xff00ff00u},
            Vertex{{0, 0, 2}, 0xff0000ffu},
        },
        {0, 1, 2}));

    Application::get().run();

    return 0;
}
