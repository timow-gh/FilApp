#ifndef MESHLER_PRESENTERCONFIG_HPP
#define MESHLER_PRESENTERCONFIG_HPP

namespace FlowMesh
{
struct PresenterConfig
{
    std::size_t spherePolarCount{16};
    std::size_t sphereAzimuthCount{20};
    std::size_t coneAzimuthCount{20};
    std::size_t cylinderAzimuthCount{20};

    std::uint32_t faceColor{0xFFc0bfbb};
    std::uint32_t selectedFaceColor{0xFF129CF3};
    std::uint32_t lineColor{0xFF000000};
    std::uint32_t selectedLineColor{0xFF000000};
};
} // namespace FlowMesh

#endif // MESHLER_PRESENTERCONFIG_HPP
