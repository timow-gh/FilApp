#include "FilApp/Application.hpp"
#include "FilApp/Renderable.hpp"
#include "FilApp/Vertex.hpp"
#include "FilApp/Window.hpp"

using namespace FilApp;

int main()
{
    Application::init(AppConfig(), WindowConfig());

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainIView();
    mainView->setUsePostprocessing(false);

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
