#include "FilApp/Renderable.hpp"
#include "generated/resources/resources.h"

namespace FilApp
{
Renderable createBakedColorRenderable(const std::vector<Vertex>& vertices,
                            const std::vector<uint16_t>& indices,
                            const filament::Box& aabb,
                            filament::Engine* engine)
{
    Renderable renderable;
    renderable.engine = engine;

    constexpr std::size_t VERTEX_SIZE = sizeof(Vertex);
    static_assert(VERTEX_SIZE == 16, "Strange vertex size.");

    const std::size_t VERTEX_COUNT = vertices.size();
    constexpr std::size_t VERTEX_POSITION_OFFSET = 0;
    constexpr std::size_t VERTEX_COLOR_OFFSET = 12;
    renderable.vb =
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
            .build(*renderable.engine);

    const std::size_t VERTICES_BUFFER_SIZE = VERTEX_COUNT * VERTEX_SIZE;
    renderable.vb->setBufferAt(
        *renderable.engine,
        0,
        filament::VertexBuffer::BufferDescriptor(vertices.data(),
                                                 VERTICES_BUFFER_SIZE,
                                                 nullptr));

    const std::size_t INDICES_COUNT = indices.size();
    renderable.ib = filament::IndexBuffer::Builder()
                        .indexCount(INDICES_COUNT)
                        .bufferType(filament::IndexBuffer::IndexType::USHORT)
                        .build(*renderable.engine);

    constexpr std::size_t INDICES_SIZE = sizeof(uint16_t);
    const std::size_t INDICES_BUFFER_SIZE = INDICES_COUNT * INDICES_SIZE;
    renderable.ib->setBuffer(
        *renderable.engine,
        filament::IndexBuffer::BufferDescriptor(indices.data(),
                                                INDICES_BUFFER_SIZE,
                                                nullptr));
    renderable.mat =
        filament::Material::Builder()
            .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
            .build(*renderable.engine);

    renderable.renderableEntity = utils::EntityManager::get().create();

    const std::size_t OFFSET = 0;
    filament::RenderableManager::Builder(1)
        .boundingBox(aabb)
        .material(0, renderable.mat->getDefaultInstance())
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::TRIANGLES,
                  renderable.vb,
                  renderable.ib,
                  OFFSET,
                  INDICES_COUNT)
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*renderable.engine, renderable.renderableEntity);

    return renderable;
}
} // namespace FilApp
