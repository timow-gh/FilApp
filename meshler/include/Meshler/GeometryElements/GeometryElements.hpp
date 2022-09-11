#ifndef MESHLER_GEOMETRYELEMENTS_HPP
#define MESHLER_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Transformation/TransformCone.hpp>
#include <Geometry/Transformation/TransformCuboid.hpp>
#include <Geometry/Transformation/TransformCylinder.hpp>
#include <Geometry/Transformation/TransformSegment.hpp>
#include <Geometry/Transformation/TransformSphere.hpp>
#include <Geometry/Transformation/TransformVec.hpp>
#include <Meshler/GeometryElements/GeomElementContainer.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

class GeometryElements {
    GeomElementContainer<MCuboid> m_cuboids;
    GeomElementContainer<MCylinder> m_cylinders;
    GeomElementContainer<MCone> m_cones;
    GeomElementContainer<MSphere> m_spheres;
    GeomElementContainer<MSegments> m_segments;
    GeomElementContainer<MGrid> m_grids;

    SnapGeometries m_snapGeometries;

  public:
    // clang-format off
    CORE_NODISCARD const GeomElementContainer<MCuboid>& getCuboids() const { return m_cuboids; }
    CORE_NODISCARD const GeomElementContainer<MCylinder>& getCylinders() const { return m_cylinders; }
    CORE_NODISCARD const GeomElementContainer<MCone>& getCones() const { return m_cones; }
    CORE_NODISCARD const GeomElementContainer<MSphere>& getSpheres() const { return m_spheres; }
    CORE_NODISCARD const GeomElementContainer<MSegments>& getSegments() const { return m_segments; }
    CORE_NODISCARD const GeomElementContainer<MGrid>& getGrids() const { return m_grids; }
    // clang-format on

    template <typename TGeomElement>
    TGeomElement& add(TGeomElement&& element)
    {
        if constexpr (std::is_same_v<TGeomElement, MCuboid>)
            return m_cuboids.add(std::forward<TGeomElement>(element));
        else if constexpr (std::is_same_v<TGeomElement, MCylinder>)
            return m_cylinders.add(std::forward<TGeomElement>(element));
        else if constexpr (std::is_same_v<TGeomElement, MCone>)
            return m_cones.add(std::forward<TGeomElement>(element));
        else if constexpr (std::is_same_v<TGeomElement, MSphere>)
            return m_spheres.add(std::forward<TGeomElement>(element));
        else if constexpr (std::is_same_v<TGeomElement, MSegments>)
            return m_segments.add(std::forward<TGeomElement>(element));
        else if constexpr (std::is_same_v<TGeomElement, MGrid>)
            return m_grids.add(std::forward<TGeomElement>(element));
    }

    template <typename TGeomElement>
    void remove(const FGuid& guid)
    {
        if constexpr (std::is_same_v<TGeomElement, MCuboid>)
            m_cuboids.remove(guid);
        else if constexpr (std::is_same_v<TGeomElement, MCylinder>)
            m_cylinders.remove(guid);
        else if constexpr (std::is_same_v<TGeomElement, MCone>)
            m_cones.remove(guid);
        else if constexpr (std::is_same_v<TGeomElement, MSphere>)
            m_spheres.remove(guid);
        else if constexpr (std::is_same_v<TGeomElement, MSegments>)
            m_segments.remove(guid);
        else if constexpr (std::is_same_v<TGeomElement, MGrid>)
            m_grids.remove(guid);
    }

    void remove(FGuid fGuid)
    {
        if (m_cuboids.remove(fGuid))
            return;
        if (m_cylinders.remove(fGuid))
            return;
        if (m_cones.remove(fGuid))
            return;
        if (m_spheres.remove(fGuid))
            return;
        if (m_segments.remove(fGuid))
            return;
        if (m_grids.remove(fGuid))
            return;
    }

    template <typename TGeomElement>
    TGeomElement* find(FGuid fGuid)
    {
        if constexpr (std::is_same_v<TGeomElement, MCuboid>)
            return m_cuboids.find(fGuid);
        else if constexpr (std::is_same_v<TGeomElement, MCylinder>)
            return m_cylinders.find(fGuid);
        else if constexpr (std::is_same_v<TGeomElement, MCone>)
            return m_cones.find(fGuid);
        else if constexpr (std::is_same_v<TGeomElement, MSphere>)
            return m_spheres.find(fGuid);
        else if constexpr (std::is_same_v<TGeomElement, MSegments>)
            return m_segments.find(fGuid);
        else if constexpr (std::is_same_v<TGeomElement, MGrid>)
            return m_grids.find(fGuid);
    }

    void updatePosition(FGuid fGuid, const LinAl::Vec3d& position)
    {
        if (auto* cuboid = find<MCuboid>(fGuid))
            cuboid->setPosition(position);
        else if (auto* cylinder = find<MCylinder>(fGuid))
            cylinder->setPosition(position);
        else if (auto* cone = find<MCone>(fGuid))
            cone->setPosition(position);
        else if (auto* sphere = find<MSphere>(fGuid))
            sphere->setPosition(position);
        else if (auto* segments = find<MSegments>(fGuid))
            segments->setPosition(position);
        else if (auto* grid = find<MGrid>(fGuid))
            grid->setPosition(position);
    }
};
} // namespace Meshler

#endif // MESHLER_GEOMETRYELEMENTS_HPP
