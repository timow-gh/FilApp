#ifndef MESHLER_PRESENTERCONFIG_HPP
#define MESHLER_PRESENTERCONFIG_HPP

namespace Meshler
{
enum class MeshDrawType
{
  WIRED,
  SURFACE_WIRED,
  SURFACE
};

struct PresenterConfig
{
  std::uint32_t polarCount{8};
  std::uint32_t azimuthCount{10};

  std::uint32_t faceColor{0xFFc0bfbb};
  std::uint32_t selectedFaceColor{0xFF129CF3};
  std::uint32_t lineColor{0xFF000000};
  std::uint32_t selectedLineColor{0xFF000000};

  MeshDrawType meshDrawType{MeshDrawType::SURFACE_WIRED};
};
} // namespace Meshler

#endif // MESHLER_PRESENTERCONFIG_HPP
