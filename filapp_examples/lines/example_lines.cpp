#include <FilApp/FilApplication.hpp>
#include <GraphicsInterface/Renderables/LineRenderable.hpp>
#include <GraphicsInterface/Vertex.hpp>
#include <GraphicsInterface/View.hpp>
#include <GraphicsInterface/Window.hpp>

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