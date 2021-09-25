#include "FilApp/FilApplication.hpp"
#include "FilApp/Interfaces/IView.hpp"
#include "FilApp/Interfaces/Renderable.hpp"

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());

    IWindow* window = FilApplication::get().getWindow();
    IView* mainView = window->getMainIView();
    mainView->setUsePostprocessing(false);

    std::vector<Vertex> vertices = {
        {{-1, 0, 0}, 0xffff0000u},
        {{1, 0, 0}, 0xff00ff00u},
        {{0, 1, 0}, 0xff0000ffu},
    };

    auto renderableId = mainView->addRenderable(
        Renderable(std::move(vertices),
                   {0, 1, 2},
                   Renderable::RenderableType::TRIANGLES));

    mainView->addRotationAnimation(renderableId, Vec3{0, 1, 0});

    FilApplication::get().run();
    return 0;
}