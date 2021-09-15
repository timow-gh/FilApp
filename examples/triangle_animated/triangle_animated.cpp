#include "FilApp/Application.hpp"
#include "FilApp/Renderable.hpp"
#include "FilApp/Vertex.hpp"
#include "FilApp/Window.hpp"
#include <filament/TransformManager.h>

using namespace FilApp;

int main()
{
    auto windowConfig = WindowConfig();

    Application::init(AppConfig(), windowConfig);

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainFilAppView();
    mainView->getFilamentView()->setPostProcessingEnabled(false);

    std::vector<Vertex> vertices = {
        {{-1, 0, 0}, 0xffff0000u},
        {{1, 0, 0}, 0xff00ff00u},
        {{0, 1, 0}, 0xff0000ffu},
    };

    std::vector<uint16_t> indices = {0, 1, 2};

    mainView->addRenderable(Renderable(vertices, indices));

//    window->addAnimationCallback(
//        [&renderable](filament::Engine* engine,
//                      filament::View* filamentView,
//                      double deltaT)
//        {
//            auto& tcm = engine->getTransformManager();
//            tcm.setTransform(tcm.getInstance(renderable.renderableEntity),
//                             filament::math::mat4f::rotation(
//                                 deltaT,
//                                 filament::math::float3{0, 1, 0}));
//        });

    Application::get().run();
    return 0;
}