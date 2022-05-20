#ifndef MESHLER_PRESENTERUTILS_HPP
#define MESHLER_PRESENTERUTILS_HPP

#include <Graphics/Vertex.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
[[nodiscard]] Graphics::Vertex vecToVertex(const LinAl::Vec3<T>& vec, std::uint32_t color)
{
    return Graphics::Vertex{
        {static_cast<float_t>(vec[0]), static_cast<float_t>(vec[1]), static_cast<float_t>(vec[2])},
        color};
}

} // namespace FlowMesh

#endif // MESHLER_PRESENTERUTILS_HPP
