#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FilApp/Interfaces/Vertex.hpp>
#include <FilApp/TriangleRenderable.hpp>
#include <vector>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();

    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, 0xffff0000u},
        Vertex{{1, 0, 0}, 0xff00ff00u},
        Vertex{{0, 0, 2}, 0xff0000ffu},
    };

    IWindow* window = app.getWindow();
    IView* mainView = window->getMainIView();

    mainView->addRenderable(TriangleRenderable(std::move(vertices), {0, 1, 2}));

    app.run();
}