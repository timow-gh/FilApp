#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FilApp/Renderables/LineRenderable.hpp>
#include <FilApp/Renderables/Vertex.hpp>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();
    IWindow* mainWindow = app.getWindow();
    IView* mainView = mainWindow->getMainIView();

    mainView->addRenderable(
        LineRenderable::create(Vertex{{0, 0, 0}, 0xffff0000u},
                               Vertex{{2, 0, 0}, 0xffff0000u}));

    mainView->addRenderable(
        LineRenderable::create(Vertex{{0, 0, 0}, 0xffff0000u},
                               Vertex{{0, 2, 0}, 0xffff0000u}));

    mainView->addRenderable(
        LineRenderable::create(Vertex{{0, 0, 0}, 0xffff0000u},
                               Vertex{{0, 0, 2}, 0xffff0000u}));

    std::vector<Vertex> vertices = {Vertex{{1, 0, 0}, 0xffff0000u},
                                    Vertex{{0, 1, 0}, 0xffff0000u},
                                    Vertex{{0, 0, 1}, 0xffff0000u},
                                    Vertex{{1, 0, 0}, 0xffff0000u}};

    mainView->addRenderable(LineRenderable::create(std::move(vertices)));

    app.run();

    return 0;
}