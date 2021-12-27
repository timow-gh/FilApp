#include "FilAppInterface/View.hpp"
#include "FilAppInterface/Window.hpp"
#include <FilApp/FilApplication.hpp>
#include <FilAppInterface/Renderables/LineRenderable.hpp>
#include <FilAppInterface/Vertex.hpp>

using namespace FilApp;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    auto& app = FilApplication::get();
    Window* mainWindow = app.getWindow();

    View* mainView = mainWindow->getMainIView();
    std::uint32_t hexColor = 0xFFc0bfbb;
    mainView->addRenderable(
        LineRenderable::create(Vertex{{0, 0, 0}, hexColor},
                               Vertex{{1, 0, 0}, hexColor}));

    std::vector<Vertex> vertices = {Vertex{{0, 0, 0}, hexColor},
                                    Vertex{{0, 2, 0}, hexColor},
                                    Vertex{{0, 0, 0}, hexColor},
                                    Vertex{{0, 0, 3}, hexColor}};
    mainView->addRenderable(LineRenderable::create(std::move(vertices)));

    app.run();
    return 0;
}