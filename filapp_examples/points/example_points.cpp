#include <FilApp/FilApplication.hpp>
#include <GraphicsInterface/Renderables/PointRenderable.hpp>
#include <GraphicsInterface/Vertex.hpp>
#include <GraphicsInterface/View.hpp>
#include <GraphicsInterface/Window.hpp>
#include <vector>

using namespace Graphics;

int main()
{
    AppConfig appConfig;
    appConfig.backendMode = BackendMode::OPENGL;
    FilApplication::init(appConfig, WindowConfig());
    auto& app = FilApplication::get();
    Window* window = app.getWindow();

    std::uint32_t hexColor = 0xFFc0bfbb;
    std::vector<Vertex> vertices = {
        Vertex{{0, 0, 0}, hexColor},
        Vertex{{1, 0, 0}, hexColor},
        Vertex{{0, 0, 2}, hexColor},
    };
    View* mainView = window->getMainIView();

    constexpr float_t POINT_SIZE = 15;
    mainView->addRenderable(
        PointRenderable::create(std::move(vertices), {POINT_SIZE, POINT_SIZE, POINT_SIZE}));
    mainView->addRenderable(PointRenderable::create(Vertex{{2, 0, 0}, hexColor}, POINT_SIZE));

    app.run();
}