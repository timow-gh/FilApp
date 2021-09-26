#include <FilApp/Renderables/LineRenderable.hpp>

namespace FilApp
{
LineRenderable LineRenderable::create(const Vertex& start, const Vertex& end)
{
    std::vector<Vertex> vertices = {start, end};
    return create(vertices);
}
LineRenderable LineRenderable::create(std::vector<Vertex> vertices)
{
    std::vector<uint16_t> indices;
    indices.reserve((vertices.size() + 1) * 2);
    const std::size_t SIZE = vertices.size();
    for (std::size_t i{1}; i < SIZE; ++i)
    {
        indices.push_back(i - 1);
        indices.push_back(i);
    }
    return {std::move(vertices), std::move(indices)};
}
} // namespace FilApp