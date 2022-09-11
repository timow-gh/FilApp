#include "FilAppRenderableBuffers.hpp"
#include <Core/Utils/Assert.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <limits>

using namespace Graphics;

namespace FilApp
{
void createVertexBuffer(FilAppRenderable* filAppRenderable, const Core::TVector<Vertex>& vertices)
{
  CORE_PRECONDITION_DEBUG_ASSERT(vertices.size() <= std::numeric_limits<uint32_t>::max(), "");

  const auto VERTEX_COUNT = static_cast<uint32_t>(vertices.size());
  const std::size_t VERTEX_SIZE = sizeof(Vertex);
  static_assert(VERTEX_SIZE == 16, "Strange vertex size.");
  CORE_CONSTEXPR std::size_t VERTEX_POSITION_OFFSET = 0;
  CORE_CONSTEXPR std::size_t VERTEX_COLOR_OFFSET = 12;
  filAppRenderable->vb =
      filament::VertexBuffer::Builder()
          .vertexCount(VERTEX_COUNT)
          .bufferCount(1)
          .attribute(filament::VertexAttribute::POSITION,
                     0,
                     filament::VertexBuffer::AttributeType::FLOAT3,
                     VERTEX_POSITION_OFFSET,
                     VERTEX_SIZE)
          .attribute(filament::VertexAttribute::COLOR, 0, filament::VertexBuffer::AttributeType::UBYTE4, VERTEX_COLOR_OFFSET, VERTEX_SIZE)
          .normalized(filament::VertexAttribute::COLOR)
          .build(*filAppRenderable->engine);

  const std::size_t VERTICES_BUFFER_SIZE = VERTEX_COUNT * VERTEX_SIZE;
  filAppRenderable->vb->setBufferAt(*filAppRenderable->engine,
                                    0,
                                    filament::VertexBuffer::BufferDescriptor(vertices.data(), VERTICES_BUFFER_SIZE, nullptr));
}

void createVertexBuffer(FilAppRenderable* filAppRenderable, PointRenderable* pointRenderable, std::uint8_t VERTEX_SIZE)
{
  const auto VERTEX_COUNT = static_cast<uint32_t>(pointRenderable->getVertices().size());
  CORE_CONSTEXPR std::size_t VERTEX_POSITION_OFFSET = 0;
  CORE_CONSTEXPR std::size_t VERTEX_COLOR_OFFSET = 12;
  filAppRenderable->vb =
      filament::VertexBuffer::Builder()
          .vertexCount(VERTEX_COUNT)
          .bufferCount(2)
          .attribute(filament::VertexAttribute::POSITION,
                     0,
                     filament::VertexBuffer::AttributeType::FLOAT3,
                     VERTEX_POSITION_OFFSET,
                     VERTEX_SIZE)
          .attribute(filament::VertexAttribute::COLOR, 0, filament::VertexBuffer::AttributeType::UBYTE4, VERTEX_COLOR_OFFSET, VERTEX_SIZE)
          .normalized(filament::VertexAttribute::COLOR)
          .attribute(filament::VertexAttribute::CUSTOM0, 1, filament::VertexBuffer::AttributeType::FLOAT, 0, sizeof(float_t))
          .build(*filAppRenderable->engine);

  const std::size_t VERTICES_BUFFER_SIZE = VERTEX_COUNT * VERTEX_SIZE;
  filAppRenderable->vb->setBufferAt(
      *filAppRenderable->engine,
      0,
      filament::VertexBuffer::BufferDescriptor(pointRenderable->getVertices().data(), VERTICES_BUFFER_SIZE, nullptr));

  filAppRenderable->vb->setBufferAt(
      *filAppRenderable->engine,
      1,
      filament::VertexBuffer::BufferDescriptor(pointRenderable->getPointSizes().data(), VERTEX_COUNT * sizeof(float_t), nullptr));
}

void createIndicesBuffer(FilAppRenderable* filAppRenderable, const Core::TVector<uint16_t>& indices)
{
  const auto INDICES_COUNT = static_cast<uint32_t>(indices.size());
  filAppRenderable->ib = filament::IndexBuffer::Builder()
                             .indexCount(INDICES_COUNT)
                             .bufferType(filament::IndexBuffer::IndexType::USHORT)
                             .build(*filAppRenderable->engine);

  CORE_CONSTEXPR std::size_t INDICES_SIZE = sizeof(uint16_t);
  const std::size_t INDICES_BUFFER_SIZE = INDICES_COUNT * INDICES_SIZE;
  filAppRenderable->ib->setBuffer(*filAppRenderable->engine,
                                  filament::IndexBuffer::BufferDescriptor(indices.data(), INDICES_BUFFER_SIZE, nullptr));
}

} // namespace FilApp
