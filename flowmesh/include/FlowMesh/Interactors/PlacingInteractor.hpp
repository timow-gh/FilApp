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

  public:
    explicit PlacingInteractor(FlowMeshModel* model) : m_model(model) {}

  private:
    FlowMeshSphere createSphere(const LinAl::Vec3d& origin)
    {
        constexpr double_t radius = 0.2;
        auto sphere = Geometry::Sphere<double_t>{origin, radius};
        return FlowMeshSphere{sphere, newFGuid()};
    }

    void event(const FilApp::PickRayEvent& pickRayEvent) override
    {
        const FilApp::Vec3& pickOrigin = pickRayEvent.origin;
        const FilApp::Vec3& pickDirection = pickRayEvent.direction;
        const Geometry::Ray3<double_t> ray{
            LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
            LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};
        const Geometry::Plane plane{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D};
        if (auto intersection = plane.intersection(ray))
        {
            FlowMeshSphere flowMeshSphere = createSphere(*intersection);
            m_model->add(flowMeshSphere);
        }
    }
    void event(const FilApp::PickRayMoveEvent& pickRayMoveEvent) override
    {
        const FilApp::Vec3& pickOrigin = pickRayMoveEvent.origin;
        const FilApp::Vec3& pickDirection = pickRayMoveEvent.direction;
        const Geometry::Ray3<double_t> ray{
            LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
            LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};
        const Geometry::Plane plane{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D};
        if (auto intersection = plane.intersection(ray))
        {
            if (!m_sphereGuid)
            {
                FlowMeshSphere flowMeshSphere = createSphere(LinAl::ZERO_VEC3D);
                m_model->add(flowMeshSphere);
                m_sphereGuid = flowMeshSphere.getFGuid();
                return;
            }
            m_model->setPosition(*m_sphereGuid, *intersection);
        }
    }
};

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
