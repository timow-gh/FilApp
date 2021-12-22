#ifndef FILAPP_PLACINGINTERACTOR_HPP
#define FILAPP_PLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <FilAppInterfaces/InputEvents/PickRayEvent.hpp>
#include <FilAppInterfaces/InputEvents/PickRayMoveEvent.hpp>
#include <FilAppInterfaces/InputEvents/RayPickEventListener.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <optional>

namespace FlowMesh
{
class PlacingInteractor : public Interactor {
    FlowMesh::FlowMeshModel* m_model;
    std::optional<FGuid> m_sphereGuid;
    std::optional<FGuid> m_rayGuid;

  public:
    explicit PlacingInteractor(FlowMeshModel* model) : m_model(model) {}

  private:
    CORE_NODISCARD FlowMeshSphere createSphere(const LinAl::Vec3d& origin) const
    {
        constexpr double_t radius = 0.2;
        auto sphere = Geometry::Sphere<double_t>{origin, radius};
        return FlowMeshSphere{sphere, newFGuid()};
    }

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcIntersection(const FilApp::PickRayEvent& pickRayEvent) const
    {
        const FilApp::Vec3& pickOrigin = pickRayEvent.origin;
        const FilApp::Vec3& pickDirection = pickRayEvent.direction;
        const Geometry::Ray3<double_t> ray{
            LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
            LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};
        const Geometry::Plane plane{LinAl::ZERO_VEC3D, LinAl::Y_VEC3D};
        return plane.intersection(ray);
    }

    void event(const FilApp::PickRayEvent& pickRayEvent) override
    {
        if (auto intersection = calcIntersection(pickRayEvent))
        {
            FlowMeshSphere flowMeshSphere = createSphere(*intersection);
            m_model->add(flowMeshSphere);
        }
    }

    void event(const FilApp::PickRayMoveEvent& pickRayMoveEvent) override
    {
        std::cout << "Ray origin: \n" << pickRayMoveEvent.origin << std::endl;
        std::cout << "Ray direction: \n" << pickRayMoveEvent.direction << std::endl << std::endl;
        if (auto intersection = calcIntersection(pickRayMoveEvent))
        {
            if (!m_sphereGuid)
            {
                FlowMeshSphere flowMeshSphere = createSphere(LinAl::ZERO_VEC3D);
                m_model->add(flowMeshSphere);
                m_sphereGuid = flowMeshSphere.getFGuid();
                return;
            }
            m_model->setPosition(*m_sphereGuid, *intersection);
            std::cout << "Intersection: \n" << *intersection << std::endl;

            //            if (m_rayGuid)
            //                m_model->remove(*m_rayGuid);
            //            LinAl::Vec3d source{pickRayMoveEvent.origin[0],
            //                                pickRayMoveEvent.origin[1],
            //                                pickRayMoveEvent.origin[2]};
            //            LinAl::Vec3d direction{pickRayMoveEvent.direction[0],
            //                                   pickRayMoveEvent.direction[1],
            //                                   pickRayMoveEvent.direction[2]};
            //            std::cout << source << std::endl;
            //            std::cout << direction << std::endl;
            //            FlowMeshSegments segments{
            //                Geometry::Segment3d{source, *intersection},
            //                newFGuid()};
            //            m_model->add(segments);
            //            m_rayGuid = segments.getFGuid();
        }
    }
};

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
