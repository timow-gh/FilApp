#include "Application.h"
#include "Window.h"
#include "generated/resources/resources.h"
#include <SDL.h>
#include <filament/RenderableManager.h>
#include <filament/TransformManager.h>
#include <utils/EntityManager.h>
#include <utils/Panic.h>

struct Vertex
{
    filament::math::float2 position;
    uint32_t color;
};

constexpr double D_PI = filament::math::d::PI;

static const Vertex TRIANGLE_VERTICES[3] = {
    {{1, 0}, 0xffff0000u},
    {{cos(D_PI * 2 / 3), sin(D_PI * 2 / 3)}, 0xff00ff00u},
    {{cos(D_PI * 4 / 3), sin(D_PI * 4 / 3)}, 0xff0000ffu},
};

static constexpr uint16_t TRIANGLE_INDICES[3] = {0, 1, 2};

namespace FilApp
{
Application::Application()
{
    initSDL();
}

void Application::initSDL()
{
    ASSERT_POSTCONDITION(SDL_Init(SDL_INIT_EVENTS) == 0, "SDL_Init Failure");
}

Application::~Application()
{
    SDL_Quit();
}

Application& Application::get()
{
    static Application app = Application();
    return app;
}
filament::Engine* Application::getEngine() const
{
    return m_engine;
}
filament::Scene* Application::getScene() const
{
    return m_scene;
}
void Application::run(const WindowConfig& windowConfig)
{
    std::unique_ptr<Window> window(new Window(windowConfig, this));

    m_scene = m_engine->createScene();
    for (auto& view: window->getViews())
        view->getFilamentView()->setScene(m_scene);

    Application::AppConfig appConfig;

    appConfig.skybox = filament::Skybox::Builder()
                           .color({0.1, 0.125, 0.25, 1.0})
                           .build(*m_engine);
    m_scene->setSkybox(appConfig.skybox);
    window->getMainView()->getFilamentView()->setPostProcessingEnabled(false);
    static_assert(sizeof(Vertex) == 12, "Strange vertex size.");
    appConfig.vb = filament::VertexBuffer::Builder()
                       .vertexCount(3)
                       .bufferCount(1)
                       .attribute(filament::VertexAttribute::POSITION,
                                  0,
                                  filament::VertexBuffer::AttributeType::FLOAT2,
                                  0,
                                  12)
                       .attribute(filament::VertexAttribute::COLOR,
                                  0,
                                  filament::VertexBuffer::AttributeType::UBYTE4,
                                  8,
                                  12)
                       .normalized(filament::VertexAttribute::COLOR)
                       .build(*m_engine);
    appConfig.vb->setBufferAt(
        *m_engine,
        0,
        filament::VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES,
                                                 36,
                                                 nullptr));
    appConfig.ib = filament::IndexBuffer::Builder()
                       .indexCount(3)
                       .bufferType(filament::IndexBuffer::IndexType::USHORT)
                       .build(*m_engine);
    appConfig.ib->setBuffer(
        *m_engine,
        filament::IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, 6, nullptr));
    appConfig.mat =
        filament::Material::Builder()
            .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
            .build(*m_engine);
    appConfig.renderable = utils::EntityManager::get().create();
    filament::RenderableManager::Builder(1)
        .boundingBox({{-1, -1, -1}, {1, 1, 1}})
        .material(0, appConfig.mat->getDefaultInstance())
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::TRIANGLES,
                  appConfig.vb,
                  appConfig.ib,
                  0,
                  3)
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*m_engine, appConfig.renderable);
    m_scene->addEntity(appConfig.renderable);

    window->addAnimationCallback(
        [&appConfig](filament::Engine* engine,
                     filament::View* filamentView,
                     double now)
        {
            auto& tcm = engine->getTransformManager();
            tcm.setTransform(tcm.getInstance(appConfig.renderable),
                             filament::math::mat4f::rotation(
                                 now,
                                 filament::math::float3{0, 0, 1}));
        });

    while (!m_closeApp)
    {
        double_t now = (double_t)SDL_GetPerformanceCounter() /
                       SDL_GetPerformanceFrequency();

        for (const auto& animationCallBack: window->getAnimationCallbacks())
            if (animationCallBack)
                animationCallBack(m_engine,
                                  window->getMainView()->getFilamentView(),
                                  now);

        constexpr Uint32 kMaxEvents = 16;
        SDL_Event events[kMaxEvents];
        Uint32 nevents = 0;
        while (nevents < kMaxEvents && SDL_PollEvent(&events[nevents]) != 0)
            nevents++;

        for (Uint32 i = 0; i < nevents; i++)
        {
            const SDL_Event& event = events[i];
            switch (event.type)
            {
            case SDL_QUIT: m_closeApp = true; break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    m_closeApp = true;
                window->keyDown(event.key.keysym.scancode);
                break;
            case SDL_KEYUP: window->keyUp(event.key.keysym.scancode); break;
            case SDL_MOUSEWHEEL: window->mouseWheel(event.wheel.y); break;
            case SDL_MOUSEBUTTONDOWN:
                window->mouseDown(event.button.button,
                                  event.button.x,
                                  event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                window->mouseUp(event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                window->mouseMoved(event.motion.x, event.motion.y);
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED: window->resize(); break;
                default: break;
                }
                break;
            default: break;
            }
        }

        // Calculate the time step.
        static Uint64 frequency = SDL_GetPerformanceFrequency();
        const float_t timeStep =
            m_timeStep > 0 ? (float_t)((double_t)(now - m_timeStep) / frequency)
                           : (float_t)(1.0f / 60.0f);
        m_timeStep = now;

        auto mainView = window->getMainView();
        if (auto mainViewManip = mainView->getCameraManipulator())
        {
            filament::math::float3 eye, center, up;
            mainViewManip->getLookAt(&eye, &center, &up);
            mainView->getCamera()->lookAt(eye, center, up);
        }

        filament::Renderer* renderer = window->getRenderer();
        if (renderer->beginFrame(window->getSwapChain()))
        {
            for (auto const& view: window->getViews())
                renderer->render(view->getFilamentView());
            renderer->endFrame();
        }
    }

    m_engine->destroy(appConfig.skybox);
    m_engine->destroy(appConfig.renderable);
    m_engine->destroy(appConfig.mat);
    m_engine->destroy(appConfig.vb);
    m_engine->destroy(appConfig.ib);
}
} // namespace FilApp
