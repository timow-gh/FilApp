#include <FilApp/Renderables/PointRenderable.hpp>
#include <numeric>

namespace FilApp
{
PointRenderable PointRenderable::create(const Vertex& vertex, float_t pointSize)
{
    return create(std::vector<Vertex>{vertex}, pointSize);
}
PointRenderable PointRenderable::create(std::vector<Vertex> vertices,
                                        float_t pointSize)
{
    const std::size_t SIZE = vertices.size();
    std::vector<uint16_t> indices(SIZE);
    std::iota(indices.begin(), indices.end(), 0);
    std::vector<float_t> pointSizes(SIZE);
    std::fill(pointSizes.begin(), pointSizes.end(), pointSize);
    return {std::move(vertices), std::move(indices), std::move(pointSizes)};
}
PointRenderable PointRenderable::create(std::vector<Vertex> vertices,
                                        std::vector<float_t> pointSizes)
{
    std::vector<uint16_t> indices(vertices.size());
    std::iota(indices.begin(), indices.end(), 0);
    return {std::move(vertices), std::move(indices), std::move(pointSizes)};
}
} // namespace FilApp