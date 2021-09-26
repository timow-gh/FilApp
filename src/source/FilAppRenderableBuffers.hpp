#ifndef FILAPP_FILAPPRENDERABLEBUFFERS_HPP
#define FILAPP_FILAPPRENDERABLEBUFFERS_HPP

#include "FilAppRenderable.hpp"

namespace FilApp
{
void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        TriangleRenderable* triangleRenderable,
                        std::size_t VERTEX_SIZE);

void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        PointRenderable* pointRenderable,
                        std::size_t VERTEX_SIZE);

void createIndicesBuffer(FilAppRenderable* filAppRenderable,
                         const std::vector<uint16_t>& indices);
} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLEBUFFERS_HPP
