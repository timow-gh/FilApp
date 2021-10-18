#include <FilApp/Renderables/LineRenderable.hpp>

namespace FilApp
{
LineRenderable LineRenderable::create(const Vertex& start, const Vertex& end)
{
    return create({start, end});
}
LineRenderable LineRenderable::create(std::vector<Vertex> vertices)
{
    assert(vertices.size() % 2 == 0);
    std::vector<uint16_t> indices;
    indices.reserve((vertices.size()));
    const std::size_t SIZE = vertices.size();
    for (std::size_t i{1}; i <= SIZE; ++i)
        indices.push_back(i - 1);
    return {std::move(vertices), std::move(indices)};
}
} // namespace FilApp