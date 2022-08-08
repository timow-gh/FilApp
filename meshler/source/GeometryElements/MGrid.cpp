#include <Meshler/GeometryElements/MGrid.hpp>

namespace Meshler
{

struct GridCalcParameters
{
    std::int64_t xNo{15};
    std::int64_t yNo{15};

    double_t xMinLength{10};
    double_t yMinLength{10};
    double_t xMaxLength{10};
    double_t yMaxLength{10};

    LinAl::Vec3d xDir{1, 0, 0};
    LinAl::Vec3d yDir{0, 1, 0};
};
void MGrid::setStepWidth(double_t stepWidth)
{
    CORE_PRECONDITION_DEBUG_ASSERT(stepWidth != 0, "");
    m_stepWidth = stepWidth;
}

void MGrid::setXMin(double_t xMin)
{
    CORE_PRECONDITION_DEBUG_ASSERT(xMin != 0, "");
    m_xMin = std::min(xMin, m_maxDistValue);
}
void MGrid::setYMin(double_t yMin)
{
    CORE_PRECONDITION_DEBUG_ASSERT(yMin != 0, "");
    m_yMin = std::min(yMin, m_maxDistValue);
}
void MGrid::setXMax(double_t xMax)
{
    CORE_PRECONDITION_DEBUG_ASSERT(xMax != 0, "");
    m_xMax = std::min(xMax, m_maxDistValue);
}
void MGrid::setYMax(double_t yMax)
{
    CORE_PRECONDITION_DEBUG_ASSERT(yMax != 0, "");
    m_yMax = std::min(yMax, m_maxDistValue);
}
void MGrid::setMaxDistValue(double_t maxDistValue)
{
    CORE_PRECONDITION_DEBUG_ASSERT(maxDistValue != 0, "");
    m_maxDistValue = maxDistValue;
}

Core::TVector<Geometry::Segment3d> MGrid::calcGridSegments() const
{
    auto gridParams = calcGridCalcParameters();

    const auto xDir = gridParams.xDir;
    const auto yDir = gridParams.yDir;
    const double_t xMin = gridParams.xMinLength;
    const double_t xMax = gridParams.xMaxLength;
    const double_t yMin = gridParams.yMinLength;
    const double_t yMax = gridParams.yMaxLength;

    Core::TVector<Geometry::Segment3d> segments;
    segments.reserve(gridParams.xNo + gridParams.yNo);

    LinAl::Vec3d xDirMin = getOrigin() - xDir * xMin;
    LinAl::Vec3d yDirMin = yDir * yMin;
    LinAl::Vec3d xSegSource = xDirMin - yDirMin;
    LinAl::Vec3d xSegTarget = xDirMin + yDir * yMax;
    segments.push_back(Geometry::Segment3d{xSegSource, xSegTarget});
    calcGridSegments(segments, xDir, gridParams.xNo);

    LinAl::Vec3d ySegTarget = getOrigin() + xDir * xMax - yDirMin;
    segments.push_back(Geometry::Segment3d{xSegSource, ySegTarget});
    calcGridSegments(segments, yDir, gridParams.yNo);

    return segments;
}

Geometry::Plane<double_t> MGrid::calcPlane() const
{
    auto trafo = getTransformation();

    LinAl::HVecd hOrig = trafo * LinAl::vec3ToHVec(getOrigin());
    LinAl::Vec3d origin = LinAl::hVecToVec3(hOrig);

    LinAl::Vec3d normal = LinAl::cross(LinAl::Vec3d{1, 0, 0}, LinAl::Vec3d{0, 1, 0});
    LinAl::HVecd hNormal = trafo * LinAl::vec3ToHVec(normal);
    normal = LinAl::hVecToVec3(hNormal);
    return {origin, normal};
}

CORE_NODISCARD LinAl::Vec3dVector MGrid::calcIntersectionPoints() const
{
    auto gridParams = calcGridCalcParameters();

    const auto xDir = gridParams.xDir;
    const auto yDir = gridParams.yDir;

    LinAl::Vec3dVector intersectionPoints;
    intersectionPoints.reserve(gridParams.xNo * gridParams.yNo);
    const LinAl::Vec3d start =
        getOrigin() - xDir * gridParams.xMinLength - yDir * gridParams.yMinLength;

    std::int64_t yNo = gridParams.yNo * 2;
    LinAl::Vec3d yDirStep = yDir * getStepWidth();
    for (std::int64_t i{0}; i < yNo; ++i)
        intersectionPoints.push_back(start + yDirStep * i);

    std::int64_t xNo = gridParams.xNo * 2;
    LinAl::Vec3d xDirStep = xDir * getStepWidth();
    for (std::int64_t i{1}; i < xNo; ++i)
    {
        auto bIter = std::reverse_iterator(intersectionPoints.end());
        auto eIter = bIter;
        std::advance(eIter, yNo);
        for (auto iter = bIter; iter < eIter; ++iter)
        {
            intersectionPoints.push_back(*iter + xDirStep);
        }
    }

    CORE_POSTCONDITION_DEBUG_ASSERT(intersectionPoints.size() == intersectionPoints.capacity(),
                                    "Missing intersection points.");

    return intersectionPoints;
}

GridCalcParameters MGrid::calcGridCalcParameters() const
{
    CORE_PRECONDITION_DEBUG_ASSERT(getXMax() + getXMin() > getStepWidth(),
                                   "stepWidth must be smaller than the grid length.");
    CORE_PRECONDITION_DEBUG_ASSERT(getYMax() + getYMin() > getStepWidth(),
                                   "stepWidth must be smaller than the grid length.");

    GridCalcParameters result;

    auto xMinNo = static_cast<std::int64_t>(getXMin() / getStepWidth());
    auto yMinNo = static_cast<std::int64_t>(getYMin() / getStepWidth());
    auto xMaxNo = static_cast<std::int64_t>(getXMax() / getStepWidth());
    auto yMaxNo = static_cast<std::int64_t>(getYMax() / getStepWidth());

    result.xNo = xMinNo + xMaxNo;
    result.yNo = yMinNo + yMaxNo;

    result.xMinLength = static_cast<double_t>(xMinNo * getStepWidth());
    result.yMinLength = static_cast<double_t>(yMinNo * getStepWidth());
    result.xMaxLength = static_cast<double_t>(xMaxNo * getStepWidth());
    result.yMaxLength = static_cast<double_t>(yMaxNo * getStepWidth());

    auto trafo = getTransformation();
    result.xDir = {1, 0, 0};
    result.yDir = {0, 1, 0};

    LinAl::HVecd hXDir = trafo * LinAl::vec3ToHVec(result.xDir);
    result.xDir = LinAl::hVecToVec3(hXDir);

    LinAl::HVecd hYDir = trafo * LinAl::vec3ToHVec(result.yDir);
    result.yDir = LinAl::hVecToVec3(hYDir);

    return result;
}

void MGrid::calcGridSegments(Core::TVector<Geometry::Segment3d>& segments,
                             LinAl::Vec3d dir,
                             std::int64_t numberOfSteps) const
{
    CORE_PRECONDITION_DEBUG_ASSERT(numberOfSteps != 0, "numberOfSteps is zero.");
    CORE_PRECONDITION_DEBUG_ASSERT(Core::isEq(LinAl::norm2(dir), 1.0),
                                   "Direction must have length 1.0");

    const LinAl::Vec3d stepDir = dir * getStepWidth();
    for (std::int64_t i{0}; i < numberOfSteps; ++i)
    {
        Geometry::Segment lastSeg = segments.back();
        segments.push_back(
            Geometry::Segment3d{lastSeg.getSource() + stepDir, lastSeg.getTarget() + stepDir});
    }
}
} // namespace Meshler