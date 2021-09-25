#include "FilApp/FilApplication.hpp"
#include "FilApp/Interfaces/IView.hpp"

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());

    IWindow* window = FilApplication::get().getWindow();
    auto mainView = window->getMainIView();
    mainView->setUsePostprocessing(false);

    mainView->addRenderable(Renderable(
        {
            Vertex{{0, 0, 0}, 0xffff0000u},
            Vertex{{1, 0, 0}, 0xff00ff00u},
            Vertex{{0, 0, 2}, 0xff0000ffu},
        },
        {0, 1, 2},
        Renderable::RenderableType::TRIANGLES));

    FilApplication::get().run();

    return 0;
}
