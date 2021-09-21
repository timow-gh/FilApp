#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FilApp/Interfaces/Renderable.hpp>
#include <FilApp/Interfaces/Vertex.hpp>
#include <vector>

using namespace FilApp;

int main()
{
    FilApplication::init(WindowConfig(), AppConfig());
    auto app = FilApplication::get();

    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, 0xffff0000u},
        Vertex{{1, 0, 0}, 0xff00ff00u},
        Vertex{{0, 0, 2}, 0xff0000ffu},
    };

    IWindow* window = app.getWindow();
    IView* mainView = window->getMainIView();

    auto pointRenderable = Renderable

    app.run();
}