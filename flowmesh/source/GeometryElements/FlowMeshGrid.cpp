#include <FlowMesh/GeometryElements/FlowMeshGrid.hpp>

namespace FlowMesh
{

FlowMeshGrid::FlowMeshGrid() : GeometryElementBase<FlowMeshGrid>(FGuid())
{
    updateSegments();
}

FlowMeshGrid::FlowMeshGrid(const FGuid& guid,
                           const LinAl::Vec3d& origin,
                           const LinAl::Vec3d& widthVec,
                           const LinAl::Vec3d& heightVec,
                           double_t stepWidth)
    : GeometryElementBase(guid)
    , m_origin(origin)
    , m_widthVec(widthVec)
    , m_heightVec(heightVec)
    , m_stepWidth(stepWidth)
{
    updateSegments();
}

void FlowMeshGrid::setSource(const LinAl::Vec3d& source)
{
    m_widthVec = source;
    updateSegments();
}

void FlowMeshGrid::setTarget(const LinAl::Vec3d& target)
{
    m_heightVec = target;
    updateSegments();
}

void FlowMeshGrid::setStepWidth(double_t stepWidth)
{
    m_stepWidth = stepWidth;
    updateSegments();
}

const LinAl::Vec3dVector& FlowMeshGrid::getIntersectionPoints() const
{
    return m_intersectionPoints;
}

void FlowMeshGrid::updateSegments()
{
    const double_t widthVecLen = LinAl::norm2(
        LinAl::Vec2d{LinAl::Vec2d{m_heightVec[0], 0} - LinAl::Vec2d{m_widthVec[0], 0}});
    const std::int64_t widthNo = static_cast<std::int64_t>(std::ceil(widthVecLen / m_stepWidth));

    const double_t heightVecLen = LinAl::norm2(
        LinAl::Vec2d{LinAl::Vec2d{0, m_heightVec[1]} - LinAl::Vec2d{0, m_widthVec[1]}});
    const std::int64_t heightNo = static_cast<std::int64_t>(std::ceil(heightVecLen / m_stepWidth));

    LinAl::Vec3d widthDirection = LinAl::normalize(m_widthVec);
    LinAl::Vec3d heightDirection = LinAl::normalize(m_heightVec);

    for (std::int64_t i{0}; i <= widthNo; ++i)
    {
        LinAl::Vec3d currentI = LinAl::Vec3d{m_origin + widthDirection * i * m_stepWidth};
        m_segments.push_back(
            Geometry::Segment3d{currentI, currentI + heightDirection * heightNo * m_stepWidth});

        for (std::int64_t j{0}; j <= heightNo; ++j)
        {
            LinAl::Vec3d point = currentI + heightDirection * j * m_stepWidth;
            m_intersectionPoints.push_back(point);
        }
    }

    for (std::int64_t j{0}; j <= heightNo; ++j)
    {
        LinAl::Vec3d currentJ = LinAl::Vec3d{m_origin + heightDirection * j * m_stepWidth};
        m_segments.push_back(
            Geometry::Segment3d{currentJ, currentJ + widthDirection * widthNo * m_stepWidth});
    }
}

} // namespace FlowMesh