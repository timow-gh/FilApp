#include "FilApp/FilApplication.hpp"
#include "FilAppInterface/View.hpp"
#include "FilAppInterface/Renderables/TriangleRenderable.hpp"
#include <FilAppInterface/Vec.hpp>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());

    Window* window = FilApplication::get().getWindow();

    std::vector<Vertex> vertices = {
        {{-1, 0, 0}, 0xffff0000u},
        {{1, 0, 0}, 0xff00ff00u},
        {{0, 1, 0}, 0xff0000ffu},
    };
    View* mainView = window->getMainIView();
    mainView->setUsePostprocessing(false);
    auto renderableId = mainView->addRenderable(
        TriangleRenderable(std::move(vertices), {0, 1, 2}));
    mainView->addRotationAnimation(renderableId, Vec3{0.0f, 1.0f, 0.0f});

    FilApplication::get().run();
    return 0;
}