#include <Meshler/GeometryElements/MGrid.hpp>

namespace FlowMesh
{

MGrid::MGrid()
    : GeometryElementBase<MGrid>(newFGuid(), MGeometryConfigBase{})
{
    updateSegments();
}

MGrid::MGrid(const FGuid& guid,
                           double_t minXLength,
                           double_t minYLength,
                           double_t maxXLength,
                           double_t maxYLength,
                           double_t stepWidth,
                           MGeometryConfigBase baseConfig)
    : GeometryElementBase(guid, baseConfig)
    , m_minXLength(minXLength)
    , m_minYLength(minYLength)
    , m_maxXLength(maxXLength)
    , m_maxYLength(maxYLength)
    , m_stepWidth(stepWidth)
{
    updateSegments();
}

void MGrid::updateSegments()
{
    m_segments.clear();
    m_intersectionPoints.clear();

    double_t flooredMinX = floorCoordAsMultipleOfStep(m_minXLength, m_stepWidth);
    double_t flooredMinY = floorCoordAsMultipleOfStep(m_minYLength, m_stepWidth);
    double_t flooredMaxX = floorCoordAsMultipleOfStep(m_maxXLength, m_stepWidth);
    double_t flooredMaxY = floorCoordAsMultipleOfStep(m_maxYLength, m_stepWidth);

    const auto xNo = static_cast<std::int64_t>((flooredMaxX - flooredMinX) / m_stepWidth);
    const auto yNo = static_cast<std::int64_t>((flooredMaxY - flooredMinY) / m_stepWidth);

    LinAl::Vec3d origin{flooredMinX, flooredMinY, 0.0};

    for (std::int64_t i{0}; i <= xNo; ++i)
    {
        LinAl::Vec3d currentI = LinAl::Vec3d{origin + LinAl::X_VEC3D * i * m_stepWidth};
        m_segments.push_back(
            Geometry::Segment3d{currentI, currentI + LinAl::Y_VEC3D * yNo * m_stepWidth});

        for (std::int64_t j{0}; j <= yNo; ++j)
        {
            LinAl::Vec3d point = currentI + LinAl::Y_VEC3D * j * m_stepWidth;
            m_intersectionPoints.push_back(point);
        }
    }

    for (std::int64_t j{0}; j <= yNo; ++j)
    {
        LinAl::Vec3d currentJ = LinAl::Vec3d{origin + LinAl::Y_VEC3D * j * m_stepWidth};
        m_segments.push_back(
            Geometry::Segment3d{currentJ, currentJ + LinAl::X_VEC3D * xNo * m_stepWidth});
    }
}

double_t MGrid::floorCoordAsMultipleOfStep(double_t coord, double_t stepWidth) const
{
    coord = std::clamp(coord, -m_maxLength, m_maxLength);
    double_t floored = std::floor(coord);
    double_t divRes = coord / stepWidth;
    double_t flooredDivRes = std::floor(divRes);
    if (divRes != flooredDivRes)
        return floored = stepWidth * flooredDivRes;
    return floored;
}

} // namespace FlowMesh