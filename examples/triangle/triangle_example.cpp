#include "FilApp/Application.h"
#include "FilApp/Renderable.h"
#include "FilApp/Window.h"
#include "generated/resources/resources.h"
#include <filament/TransformManager.h>

using namespace FilApp;

constexpr double D_PI = filament::math::d::PI;

static const Vertex TRIANGLE_VERTICES[3] = {
    {{0, 0, 0}, 0xffff0000u},
    {{1, 0, 0}, 0xff00ff00u},
    {{0, 0, 2}, 0xff0000ffu},
};

static constexpr uint16_t TRIANGLE_INDICES[3] = {0, 1, 2};

Renderable createTriangle(filament::Engine* engine,
                          const Vertex triangleVertices[3],
                          const uint16_t triangleIndices[3])
{
    Renderable renderable;
    renderable.engine = engine;

    static_assert(sizeof(Vertex) == 16, "Strange vertex size.");
    renderable.vb =
        filament::VertexBuffer::Builder()
            .vertexCount(3)
            .bufferCount(1)
            .attribute(filament::VertexAttribute::POSITION,
                       0,
                       filament::VertexBuffer::AttributeType::FLOAT3,
                       0,
                       16)
            .attribute(filament::VertexAttribute::COLOR,
                       0,
                       filament::VertexBuffer::AttributeType::UBYTE4,
                       12,
                       16)
            .normalized(filament::VertexAttribute::COLOR)
            .build(*renderable.engine);
    renderable.vb->setBufferAt(
        *renderable.engine,
        0,
        filament::VertexBuffer::BufferDescriptor(triangleVertices,
                                                 48,
                                                 nullptr));
    renderable.ib = filament::IndexBuffer::Builder()
                        .indexCount(3)
                        .bufferType(filament::IndexBuffer::IndexType::USHORT)
                        .build(*renderable.engine);
    renderable.ib->setBuffer(
        *renderable.engine,
        filament::IndexBuffer::BufferDescriptor(triangleIndices, 6, nullptr));

    renderable.mat =
        filament::Material::Builder()
            .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
            .build(*renderable.engine);

    renderable.renderableEntity = utils::EntityManager::get().create();
    filament::RenderableManager::Builder(1)
        .boundingBox({{-10, -10, -10}, {10, 10, 10}})
        .material(0, renderable.mat->getDefaultInstance())
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::TRIANGLES,
                  renderable.vb,
                  renderable.ib,
                  0,
                  3)
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*renderable.engine, renderable.renderableEntity);

    return renderable;
}

int main()
{
    auto windowConfig = WindowConfig();
    windowConfig.cameraMode = filament::camutils::Mode::MAP;

    Application::init(AppConfig(), windowConfig);

    Window* window = Application::get().getWindow();
    auto mainView = window->getMainView();
    mainView->getFilamentView()->setPostProcessingEnabled(false);

    auto renderable = createTriangle(Application::get().getEngine(),
                                     TRIANGLE_VERTICES,
                                     TRIANGLE_INDICES);

    mainView->addRenderable(renderable);

//    window->addAnimationCallback(
//        [&renderable](filament::Engine* engine,
//                      filament::View* filamentView,
//                      double deltaT)
//        {
//            auto& tcm = engine->getTransformManager();
//            tcm.setTransform(tcm.getInstance(renderable.renderableEntity),
//                             filament::math::mat4f::rotation(
//                                 deltaT,
//                                 filament::math::float3{0, 0, 1}));
//        });

    Application::get().run();
    return 0;
}
