#include "FilAppRenderable.hpp"
#include "generated/resources/filapp_resources.h"
#include "math/vec2.h"

namespace FilApp
{
FilAppRenderable
createBakedColorRenderable(TriangleRenderable* triangleRenderable,
                           const filament::Box& aabb,
                           filament::Engine* engine)
{
    FilAppRenderable filAppRenderable;
    filAppRenderable.engine = engine;

    constexpr std::size_t VERTEX_SIZE = sizeof(Vertex);
    static_assert(VERTEX_SIZE == 16, "Strange vertex size.");

    const std::size_t VERTEX_COUNT = triangleRenderable->getVertices().size();
    constexpr std::size_t VERTEX_POSITION_OFFSET = 0;
    constexpr std::size_t VERTEX_COLOR_OFFSET = 12;
    filAppRenderable.vb =
        filament::VertexBuffer::Builder()
            .vertexCount(VERTEX_COUNT)
            .bufferCount(1)
            .attribute(filament::VertexAttribute::POSITION,
                       0,
                       filament::VertexBuffer::AttributeType::FLOAT3,
                       VERTEX_POSITION_OFFSET,
                       VERTEX_SIZE)
            .attribute(filament::VertexAttribute::COLOR,
                       0,
                       filament::VertexBuffer::AttributeType::UBYTE4,
                       VERTEX_COLOR_OFFSET,
                       VERTEX_SIZE)
            .normalized(filament::VertexAttribute::COLOR)
            .build(*filAppRenderable.engine);

    const std::size_t VERTICES_BUFFER_SIZE = VERTEX_COUNT * VERTEX_SIZE;
    filAppRenderable.vb->setBufferAt(
        *filAppRenderable.engine,
        0,
        filament::VertexBuffer::BufferDescriptor(
            triangleRenderable->getVertices().data(),
            VERTICES_BUFFER_SIZE,
            nullptr));

    const std::size_t INDICES_COUNT = triangleRenderable->getIndices().size();
    filAppRenderable.ib =
        filament::IndexBuffer::Builder()
            .indexCount(INDICES_COUNT)
            .bufferType(filament::IndexBuffer::IndexType::USHORT)
            .build(*filAppRenderable.engine);

    constexpr std::size_t INDICES_SIZE = sizeof(uint16_t);
    const std::size_t INDICES_BUFFER_SIZE = INDICES_COUNT * INDICES_SIZE;
    filAppRenderable.ib->setBuffer(*filAppRenderable.engine,
                                   filament::IndexBuffer::BufferDescriptor(
                                       triangleRenderable->getIndices().data(),
                                       INDICES_BUFFER_SIZE,
                                       nullptr));
    filAppRenderable.mat = filament::Material::Builder()
                               .package(FILAPP_RESOURCES_BAKEDFRAGCOLOR_DATA,
                                        FILAPP_RESOURCES_BAKEDFRAGCOLOR_SIZE)
                               .build(*filAppRenderable.engine);

    filAppRenderable.renderableEntity = utils::EntityManager::get().create();

    const std::size_t OFFSET = 0;
    filament::RenderableManager::Builder(1)
        .boundingBox(aabb)
        .material(0, filAppRenderable.mat->getDefaultInstance())
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::TRIANGLES,
                  filAppRenderable.vb,
                  filAppRenderable.ib,
                  OFFSET,
                  INDICES_COUNT)
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*filAppRenderable.engine, filAppRenderable.renderableEntity);

    return filAppRenderable;
}

FilAppRenderable createBakedColorRenderable(PointRenderable* renderable,
                                            const filament::Box& aabb,
                                            filament::Engine* engine)
{
    FilAppRenderable filAppRenderable;
    filAppRenderable.engine = engine;

    constexpr std::size_t VERTEX_SIZE = sizeof(Vertex);

    const std::size_t VERTEX_COUNT = renderable->getVertices().size();
    constexpr std::size_t VERTEX_POSITION_OFFSET = 0;
    constexpr std::size_t VERTEX_COLOR_OFFSET = 12;
    filAppRenderable.vb =
        filament::VertexBuffer::Builder()
            .vertexCount(VERTEX_COUNT)
            .bufferCount(2)
            .attribute(filament::VertexAttribute::POSITION,
                       0,
                       filament::VertexBuffer::AttributeType::FLOAT3,
                       VERTEX_POSITION_OFFSET,
                       VERTEX_SIZE)
            .attribute(filament::VertexAttribute::COLOR,
                       0,
                       filament::VertexBuffer::AttributeType::UBYTE4,
                       VERTEX_COLOR_OFFSET,
                       VERTEX_SIZE)
            .normalized(filament::VertexAttribute::COLOR)
            .attribute(filament::VertexAttribute::CUSTOM0,
                       1,
                       filament::VertexBuffer::AttributeType::FLOAT,
                       0,
                       sizeof(float))
            .build(*engine);

    const std::size_t VERTICES_BUFFER_SIZE = VERTEX_COUNT * VERTEX_SIZE;
    filAppRenderable.vb->setBufferAt(*engine,
                                     0,
                                     filament::VertexBuffer::BufferDescriptor(
                                         renderable->getVertices().data(),
                                         VERTICES_BUFFER_SIZE,
                                         nullptr));

    filAppRenderable.vb->setBufferAt(*engine,
                                     1,
                                     filament::VertexBuffer::BufferDescriptor(
                                         renderable->getPointSizes().data(),
                                         VERTEX_COUNT * sizeof(float),
                                         nullptr));

    const std::size_t INDICES_COUNT = renderable->getIndices().size();
    filAppRenderable.ib =
        filament::IndexBuffer::Builder()
            .indexCount(INDICES_COUNT)
            .bufferType(filament::IndexBuffer::IndexType::USHORT)
            .build(*engine);

    constexpr std::size_t INDICES_SIZE = sizeof(uint16_t);
    const std::size_t INDICES_BUFFER_SIZE = INDICES_COUNT * INDICES_SIZE;
    filAppRenderable.ib->setBuffer(
        *engine,
        filament::IndexBuffer::BufferDescriptor(renderable->getIndices().data(),
                                                INDICES_BUFFER_SIZE,
                                                nullptr));

    filAppRenderable.mat = filament::Material::Builder()
                               .package(FILAPP_RESOURCES_BAKEDVERTEXCOLOR_DATA,
                                        FILAPP_RESOURCES_BAKEDVERTEXCOLOR_SIZE)
                               .build(*engine);

    filAppRenderable.renderableEntity = utils::EntityManager::get().create();
    filAppRenderable.matInstance = filAppRenderable.mat->createInstance();

    filament::RenderableManager::Builder(1)
        .boundingBox({{-1, -1, -1}, {1, 1, 1}})
        .material(0, filAppRenderable.matInstance)
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::POINTS,
                  filAppRenderable.vb,
                  filAppRenderable.ib,
                  0,
                  INDICES_COUNT)
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*engine, filAppRenderable.renderableEntity);

    return filAppRenderable;
}
} // namespace FilApp
