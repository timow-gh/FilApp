#include "FilAppInterfaces/IView.hpp"
#include "FilAppInterfaces/IWindow.hpp"
#include <FilApp/FilApplication.hpp>
#include <FilAppInterfaces/Renderables/LineRenderable.hpp>
#include <FilAppInterfaces/Vertex.hpp>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();
    IWindow* mainWindow = app.getWindow();
    IView* mainView = mainWindow->getMainIView();

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