#include <Core/Math/Eps.hpp>
#include <Geometry/Intersection/IntersectionPlane.hpp>
#include <Geometry/Ray.hpp>
#include <Meshler/Interactors/MGridInteractor.hpp>
#include <Meshler/LinAlConversion.hpp>
#include <Meshler/MModel.hpp>
#include <utility>

namespace Meshler
{

MGridInteractor::MGridInteractor(MModel& model, FGuid defaultGridGuid)
    : m_model(model), m_activeGridGuid(defaultGridGuid)
{
    auto* grid = m_model.get().get<MGrid>(defaultGridGuid);
    CORE_POSTCONDITION_DEBUG_ASSERT(grid,
                                    "Model does not contain element with the defaultGridGuid.");
    if (grid)
    {
        m_gridCopy = *grid;
        m_activeGridPlane = m_gridCopy.calcPlane();
    }
}

std::optional<LinAl::Vec3d>
MGridInteractor::rayIntersection(const Graphics::PickRayEvent& pickRayEvent) const
{
    const Geometry::Ray3<double_t> ray{vec3ToLinAlVec3<double_t>(pickRayEvent.origin),
                                       vec3ToLinAlVec3<double_t>(pickRayEvent.direction)};

    return Geometry::intersection(m_activeGridPlane, ray);
}

void MGridInteractor::onEvent(const Graphics::PickRayEvent& pickRayEvent)
{
    std::optional<LinAl::Vec3d> intersectionVec = rayIntersection(pickRayEvent);
    if (!intersectionVec)
        return;

    double_t xMin = m_gridCopy.getXMin();
    double_t yMin = m_gridCopy.getYMin();
    double_t xMax = m_gridCopy.getXMax();
    double_t yMax = m_gridCopy.getYMax();

    if (updatedLengths(*intersectionVec, xMin, yMin, xMax, yMax))
    {
        m_model.get().remove(m_activeGridGuid);

        MGrid newGrid = m_gridCopy;
        newGrid.setXMin(xMin);
        newGrid.setYMin(yMin);
        newGrid.setXMax(xMax);
        newGrid.setYMax(yMax);
        m_activeGridGuid = newGrid.getFGuid();
        m_gridCopy = newGrid;
        m_model.get().add(std::move(newGrid));
    }
}

void MGridInteractor::onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent)
{
    double_t deltaT = pickRayMoveEvent.time - m_lastUpdateTime;
    m_lastUpdateTime = pickRayMoveEvent.time;
    if (deltaT > m_updateTimeDelta)
        return;

    std::optional<LinAl::Vec3d> intersectionVec = rayIntersection(pickRayMoveEvent);
    if (!intersectionVec)
        return;

    double_t diff = LinAl::norm2(LinAl::Vec3d{*intersectionVec - m_pevGridIntersectionPoint});
    if (Core::isLess(diff, m_diffUpdateDistance))
        return;

    m_pevGridIntersectionPoint = *intersectionVec;

    double_t xMin = m_gridCopy.getXMin();
    double_t yMin = m_gridCopy.getYMin();
    double_t xMax = m_gridCopy.getXMax();
    double_t yMax = m_gridCopy.getYMax();

    if (updatedLengths(*intersectionVec, xMin, yMin, xMax, yMax))
    {
        MModel& model = m_model.get();
        auto* activeGrid = model.get<MGrid>(m_activeGridGuid);
        CORE_POSTCONDITION_DEBUG_ASSERT(activeGrid, "");
        if (!activeGrid)
            return;

        activeGrid->setXMin(xMin);
        activeGrid->setYMin(yMin);
        activeGrid->setXMax(xMax);
        activeGrid->setYMax(yMax);
        model.update(m_activeGridGuid);
    }
}
bool MGridInteractor::updatedLengths(LinAl::Vec3d intersectionVec,
                                     double_t& xMin,
                                     double_t& yMin,
                                     double_t& xMax,
                                     double_t& yMax)
{
    LinAl::Vec3d distVec = intersectionVec - m_gridCopy.getOrigin();
    bool updated{false};
    double_t updateDist = m_gridCopy.getStepWidth() * m_updateDistMultiplier;
    double_t xDist = distVec[0];
    if (Core::isLess(xDist, 0.0))
    {
        if (m_gridCopy.getXMin() - updateDist < std::abs(xDist))
        {
            xMin = std::abs(xDist) + updateDist;
            updated = true;
        }
    }
    else
    {
        if (m_gridCopy.getXMax() - updateDist < std::abs(xDist))
        {
            xMax = std::abs(xDist) + updateDist;
            updated = true;
        }
    }

    double_t yDist = distVec[1];
    if (Core::isLess(yDist, 0.0))
    {
        if (m_gridCopy.getYMin() - updateDist < std::abs(yDist))
        {
            yMin = std::abs(yDist) + updateDist;
            updated = true;
        }
    }
    else
    {
        if (m_gridCopy.getYMax() - updateDist < std::abs(yDist))
        {
            yMax = std::abs(yDist) + updateDist;
            updated = true;
        }
    }

    return updated;
}

} // namespace Meshler
