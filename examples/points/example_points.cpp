#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FilApp/Renderables/PointRenderable.hpp>
#include <FilApp/Renderables/Vertex.hpp>
#include <vector>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();

    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, 0xffff0000u},
        Vertex{{1, 0, 0}, 0xffff0000u},
        Vertex{{0, 0, 2}, 0xffff0000u},
    };

    IWindow* window = app.getWindow();
    IView* mainView = window->getMainIView();

    mainView->addRenderable(
        PointRenderable(std::move(vertices), {0, 1, 2}, {4.0, 4.0, 4.0}));

    app.run();
}