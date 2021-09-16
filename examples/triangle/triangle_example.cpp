#include "FilApp/Application.hpp"
#include "FilApp/FilWindow.hpp"
#include "FilApp/Interfaces/Renderable.hpp"
#include "FilApp/Interfaces/Vertex.hpp"

using namespace FilApp;

int main()
{
    Application::init(AppConfig(), WindowConfig());

    FilWindow* window = Application::get().getWindow();
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
