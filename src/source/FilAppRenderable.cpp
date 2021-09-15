#include "FilApp/FilAppRenderable.hpp"
#include "generated/resources/filapp_resources.h"

namespace FilApp
{
FilAppRenderable createBakedColorRenderable(Renderable&& renderable,
                                            const filament::Box& aabb,
                                            filament::Engine* engine)
{
    FilAppRenderable filAppRenderable;
    filAppRenderable.renderable =
        std::make_unique<Renderable>(std::move(renderable));
    filAppRenderable.engine = engine;

    constexpr std::size_t VERTEX_SIZE = sizeof(Vertex);
    static_assert(VERTEX_SIZE == 16, "Strange vertex size.");

    const std::size_t VERTEX_COUNT =
        filAppRenderable.renderable->getVertices().size();
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
            filAppRenderable.renderable->getVertices().data(),
            VERTICES_BUFFER_SIZE,
            nullptr));

    const std::size_t INDICES_COUNT =
        filAppRenderable.renderable->getIndices().size();
    filAppRenderable.ib =
        filament::IndexBuffer::Builder()
            .indexCount(INDICES_COUNT)
            .bufferType(filament::IndexBuffer::IndexType::USHORT)
            .build(*filAppRenderable.engine);

    constexpr std::size_t INDICES_SIZE = sizeof(uint16_t);
    const std::size_t INDICES_BUFFER_SIZE = INDICES_COUNT * INDICES_SIZE;
    filAppRenderable.ib->setBuffer(
        *filAppRenderable.engine,
        filament::IndexBuffer::BufferDescriptor(
            filAppRenderable.renderable->getIndices().data(),
            INDICES_BUFFER_SIZE,
            nullptr));
    filAppRenderable.mat = filament::Material::Builder()
                               .package(FILAPP_RESOURCES_BAKEDCOLOR_DATA,
                                        FILAPP_RESOURCES_BAKEDCOLOR_SIZE)
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
} // namespace FilApp
