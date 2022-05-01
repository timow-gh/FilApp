#include "FlowMeshGridInteractor.hpp"
#include <Core/Math/Eps.hpp>

namespace FlowMesh
{

std::unique_ptr<FlowMeshGridInteractor> FlowMeshGridInteractor::create(FlowMeshModel& model,
                                                                       const FlowMeshGrid& grid)
{
    model.add(grid);
    return std::make_unique<FlowMeshGridInteractor>(FlowMeshGridInteractor(model, grid.getFGuid()));
}

FlowMeshGridInteractor::FlowMeshGridInteractor(FlowMeshModel& model, const FGuid& fGuid)
    : m_model(&model), m_gridGuid(fGuid)
{
}

void FlowMeshGridInteractor::onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent)
{
    Geometry::Plane<double_t> plane{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D};

    const Graphics::Vec3& pickOrigin = pickRayMoveEvent.origin;
    const Graphics::Vec3& pickDirection = pickRayMoveEvent.direction;
    const Geometry::Ray3<double_t> ray{
        LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
        LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};

    std::optional<LinAl::Vec3d> result = plane.intersection(ray);
    if (!result)
        return;

    double_t diff = LinAl::norm2(LinAl::Vec3d{*result - m_pevGridIntersectionPoint});
    if (Core::isLess(diff, m_diffUpdateDistance))
        return;

    double_t xCoord = (*result)[0];
    double_t yCoord = (*result)[1];

    auto* grid = m_model->get<FlowMeshGrid>(m_gridGuid);
    if (!grid)
        return;

    FlowMeshGrid newGrid = *grid;

    double_t flooredXCoord = std::floor(xCoord);
    bool updated{false};
    if (Core::isLess(xCoord, m_minimalGrid.getMinXLength() + m_updateDistance) &&
        Core::isLess(xCoord, newGrid.getMinXLength() + m_updateDistance))
    {
        // Extend xMin to cursor
        newGrid.setMinXLength(flooredXCoord - m_updateDistance);
        updated = true;
    }
    else if (Core::isLess(xCoord, m_minimalGrid.getMinXLength() + m_updateDistance) &&
             Core::isGreater(xCoord, newGrid.getMinXLength() + m_updateDistance))
    {
        // Shrink xMin to cursor
        newGrid.setMinXLength(flooredXCoord - m_updateDistance);
        updated = true;
    }
    else if (Core::isGreater(xCoord, m_minimalGrid.getMinXLength() + m_updateDistance) &&
             !Core::isEq(newGrid.getMinXLength(), m_minimalGrid.getMinXLength() + m_updateDistance))
    {
        // Shrink xMin to minimal grid
        newGrid.setMinXLength(m_minimalGrid.getMinXLength());
        updated = true;
    }

    double_t flooredYCoord = std::floor(yCoord);
    if (Core::isLess(yCoord, (m_minimalGrid.getMinYLength() + m_updateDistance)) &&
        Core::isLess(yCoord, (newGrid.getMinYLength() + m_updateDistance)))
    {
        // Extend yMin to cursor
        newGrid.setMinYLength(flooredYCoord - m_updateDistance);
        updated = true;
    }
    else if (Core::isLess(yCoord, (m_minimalGrid.getMinYLength() + m_updateDistance)) &&
             Core::isGreater(yCoord, newGrid.getMinYLength() + m_updateDistance))
    {
        // Shrink yMin to cursor
        newGrid.setMinYLength(flooredYCoord - m_updateDistance);
        updated = true;
    }
    else if (Core::isGreater(yCoord, m_minimalGrid.getMinYLength() + m_updateDistance) &&
             !Core::isEq(newGrid.getMinYLength(), m_minimalGrid.getMinYLength() + m_updateDistance))
    {
        // Shrink yMin to minimal grid
        newGrid.setMinYLength(m_minimalGrid.getMinYLength());
        updated = true;
    }

    double_t ceilXCoord = std::ceil(xCoord);
    if (Core::isGreater(xCoord, m_minimalGrid.getMaxXLength() - m_updateDistance) &&
        Core::isGreater(xCoord, newGrid.getMaxXLength() - m_updateDistance))
    {
        // Extend xMax to cursor
        newGrid.setMaxXLength(ceilXCoord + m_updateDistance);
        updated = true;
    }
    else if (Core::isGreater(xCoord, m_minimalGrid.getMaxXLength() - m_updateDistance) &&
             Core::isLess(xCoord, newGrid.getMaxXLength() - m_updateDistance))
    {
        // Shrink xMax to cursor
        newGrid.setMaxXLength(ceilXCoord + m_updateDistance);
        updated = true;
    }
    else if (Core::isLess(xCoord, m_minimalGrid.getMaxXLength() - m_updateDistance) &&
             !Core::isEq(newGrid.getMaxXLength(), m_minimalGrid.getMaxXLength() - m_updateDistance))
    {
        // Shrink xMax to minimal grid
        newGrid.setMaxXLength(m_minimalGrid.getMaxXLength());
        updated = true;
    }

    double_t ceilYCoord = std::ceil(yCoord);
    if (Core::isGreater(yCoord, m_minimalGrid.getMaxYLength() - m_updateDistance) &&
        Core::isGreater(yCoord, newGrid.getMaxYLength() - m_updateDistance))
    {
        // Extend yMax to cursor
        newGrid.setMaxYLength(ceilYCoord + m_updateDistance);
        updated = true;
    }
    else if (Core::isGreater(yCoord, m_minimalGrid.getMaxYLength() - m_updateDistance) &&
             Core::isLess(yCoord, newGrid.getMaxYLength() - m_updateDistance))
    {
        // Shrink yMax to cursor
        newGrid.setMaxYLength(ceilYCoord + m_updateDistance);
        updated = true;
    }
    else if (Core::isLess(yCoord, m_minimalGrid.getMaxYLength() - m_updateDistance) &&
             !Core::isEq(newGrid.getMaxYLength(), m_minimalGrid.getMaxYLength() - m_updateDistance))
    {
        // Shrink yMax to minimal grid
        newGrid.setMaxYLength(m_minimalGrid.getMaxYLength());
        updated = true;
    }

    if (updated)
    {
        newGrid.updateSegments();
        m_model->add(newGrid);
        m_model->remove(m_gridGuid);
        m_gridGuid = newGrid.getFGuid();
    }
}

} // namespace FlowMesh
