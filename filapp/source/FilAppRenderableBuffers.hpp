#ifndef FILAPP_FILAPPRENDERABLEBUFFERS_HPP
#define FILAPP_FILAPPRENDERABLEBUFFERS_HPP

#include <FilApp/FilAppRenderable.hpp>

namespace Graphics
{
void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        const std::vector<Vertex>& vertices);

void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        PointRenderable* pointRenderable,
                        std::size_t VERTEX_SIZE);

void createIndicesBuffer(FilAppRenderable* filAppRenderable,
                         const std::vector<uint16_t>& indices);
} // namespace Graphics

#endif // FILAPP_FILAPPRENDERABLEBUFFERS_HPP
