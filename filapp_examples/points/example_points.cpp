#include "../../filapp_interfaces/IView.hpp"
#include "../../filapp_interfaces/IWindow.hpp"
#include <FilApp/FilApplication.hpp>
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
        PointRenderable::create(std::move(vertices), {3.0, 3.0, 3.0}));
    mainView->addRenderable(
        PointRenderable::create(Vertex{{2, 0, 0}, 0xffff0000u}, 15.0));

    app.run();
}