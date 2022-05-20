#ifndef MESHLER_LINALCONVERSION_HPP
#define MESHLER_LINALCONVERSION_HPP

#include <Graphics/Vec.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
LinAl::HVec<T> vec4ToHVec(const Graphics::Vec4& vec4)
{
    return LinAl::HVec<T>{static_cast<T>(vec4[0]),
                          static_cast<T>(vec4[1]),
                          static_cast<T>(vec4[2]),
                          static_cast<T>(vec4[3])};
}

template <typename T>
Graphics::Vec4 hVecToVec4(const LinAl::HVec<T>& vec4)
{
    return Graphics::Vec4{static_cast<T>(vec4[0]),
                          static_cast<T>(vec4[1]),
                          static_cast<T>(vec4[2]),
                          static_cast<T>(vec4[3])};
}

template <typename T>
LinAl::Vec3<T> vec3ToLinAlVec3(const Graphics::Vec3& vec3)
{
    return LinAl::Vec3<T>{static_cast<T>(vec3[0]),
                          static_cast<T>(vec3[1]),
                          static_cast<T>(vec3[2])};
}

template <typename T>
Graphics::Vec3 linAlVec3ToVec3(const LinAl::Vec3<T>& vec3)
{
    return Graphics::Vec3{static_cast<T>(vec3[0]),
                          static_cast<T>(vec3[1]),
                          static_cast<T>(vec3[2])};
}

} // namespace FlowMesh

#endif // MESHLER_LINALCONVERSION_HPP
