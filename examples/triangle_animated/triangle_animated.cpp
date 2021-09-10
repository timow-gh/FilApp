#include "../ExampleTriangle.hpp"
#include "FilApp/Window.hpp"
#include <filament/TransformManager.h>

using namespace FilApp;

int main()
{
    auto windowConfig = WindowConfig();
    windowConfig.cameraMode = filament::camutils::Mode::ORBIT;

    Application::init(AppConfig(), windowConfig);

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainView();
    mainView->getFilamentView()->setPostProcessingEnabled(false);

    auto renderable = createTriangle(Application::get().getEngine(),
                                     TRIANGLE_VERTICES,
                                     TRIANGLE_INDICES);

    mainView->addRenderable(renderable);

    window->addAnimationCallback(
        [&renderable](filament::Engine* engine,
                      filament::View* filamentView,
                      double deltaT)
        {
            auto& tcm = engine->getTransformManager();
            tcm.setTransform(tcm.getInstance(renderable.renderableEntity),
                             filament::math::mat4f::rotation(
                                 deltaT,
                                 filament::math::float3{0, 1, 0}));
        });

    Application::get().run();
    return 0;
}