#ifndef FILAPP_FILAPPRENDERABLEBUFFERS_HPP
#define FILAPP_FILAPPRENDERABLEBUFFERS_HPP

#include <Core/Types/TVector.hpp>
#include <FilApp/FilAppRenderable.hpp>

namespace FilApp
{
void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        const Core::TVector<Graphics::Vertex>& vertices);

void createVertexBuffer(FilAppRenderable* filAppRenderable,
                        Graphics::PointRenderable* pointRenderable,
                        std::size_t VERTEX_SIZE);

void createIndicesBuffer(FilAppRenderable* filAppRenderable,
                         const Core::TVector<uint16_t>& indices);
} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLEBUFFERS_HPP
