#include "FilApp/Application.hpp"
#include "FilApp/IView.hpp"
#include "FilApp/Renderable.hpp"
#include "FilApp/Vec3.hpp"
#include "FilApp/Vertex.hpp"
#include "FilApp/Window.hpp"

using namespace FilApp;

int main()
{
    Application::init(AppConfig(), WindowConfig());

    Window* window = Application::get().getWindow();
    IView* mainView = window->getMainIView();
    mainView->setUsePostprocessing(false);

    std::vector<Vertex> vertices = {
        {{-1, 0, 0}, 0xffff0000u},
        {{1, 0, 0}, 0xff00ff00u},
        {{0, 1, 0}, 0xff0000ffu},
    };

    auto renderableId =
        mainView->addRenderable(Renderable(std::move(vertices), {0, 1, 2}));

    mainView->addRotationAnimation(renderableId, Vec3{0, 1, 0});

    Application::get().run();
    return 0;
}