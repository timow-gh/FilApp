#include "FilAppInterfaces/View.hpp"
#include "FilAppInterfaces/Window.hpp"
#include <FilApp/FilApplication.hpp>
#include <FilAppInterfaces/Renderables/LineRenderable.hpp>
#include <FilAppInterfaces/Vertex.hpp>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();
    Window* mainWindow = app.getWindow();

    View* mainView = mainWindow->getMainIView();
    mainView->addRenderable(
        LineRenderable::create(Vertex{{0, 0, 0}, 0xffffffffu},
                               Vertex{{1, 0, 0}, 0xffffffffu}));

    std::vector<Vertex> vertices = {Vertex{{0, 0, 0}, 0xffffffffu},
                                    Vertex{{0, 2, 0}, 0xffffffffu},
                                    Vertex{{0, 0, 0}, 0xffffffffu},
                                    Vertex{{0, 0, 3}, 0xffffffffu}};
    mainView->addRenderable(LineRenderable::create(std::move(vertices)));

    app.run();
    return 0;
}