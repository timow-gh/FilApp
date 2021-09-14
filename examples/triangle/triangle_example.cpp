#include "FilApp/Application.hpp"
#include "FilApp/Vertex.hpp"
#include "FilApp/Window.hpp"

using namespace FilApp;

int main()
{
    auto windowConfig = WindowConfig();
    Application::init(AppConfig(), windowConfig);

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainView();
    mainView->getFilamentView()->setPostProcessingEnabled(false);

    std::vector<Vertex> vertices = {
        {{0, 0, 0}, 0xffff0000u},
        {{1, 0, 0}, 0xff00ff00u},
        {{0, 0, 2}, 0xff0000ffu},
    };

    std::vector<uint16_t> indices = {0, 1, 2};

    auto renderable =
        createBakedColorRenderable(vertices,
                                   indices,
                                   filament::Box{{0, 0, 0}, {10, 10, 10}},
                                   Application::get().getEngine());

    mainView->addRenderable(renderable);

    Application::get().run();
    return 0;
}
