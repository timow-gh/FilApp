#ifndef FILAPP_PLACINGINTERACTOR_HPP
#define FILAPP_PLACINGINTERACTOR_HPP

#include "Geometry/Ray.hpp"
#include <Core/Types/TVector.hpp>
#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <FilAppInterfaces/InputEvents/PickRayEvent.hpp>
#include <FilAppInterfaces/InputEvents/PickRayMoveEvent.hpp>
#include <FilAppInterfaces/InputEvents/RayPickEventListener.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <Geometry/Plane.hpp>
#include <optional>

namespace FlowMesh
{
class PlacingInteractor : public Interactor {
    FlowMesh::FlowMeshModel* m_model;
    std::optional<FGuid> m_tmpPointGuid;

  public:
    explicit PlacingInteractor(FlowMeshModel* model) : m_model(model) {}

  private:
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
            constexpr double_t radius = 0.2;
            auto sphere = Geometry::Sphere<double_t>{*intersection, radius};
            FlowMeshSphere flowMeshSphere{sphere, newFGuid()};
            m_tmpPointGuid = flowMeshSphere.getFGuid();
            m_model->add(flowMeshSphere);
        }
    }
    void event(const FilApp::PickRayMoveEvent& pickRayMoveEvent) override
    {
        if (m_tmpPointGuid)
            m_model->remove(*m_tmpPointGuid);
        const FilApp::Vec3& pickOrigin = pickRayMoveEvent.origin;
        const FilApp::Vec3& pickDirection = pickRayMoveEvent.direction;
        const Geometry::Ray3<double_t> ray{
            LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
            LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};
        const Geometry::Plane plane{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D};
        if (auto intersection = plane.intersection(ray))
        {
            std::cout << "intersection: \n" << *intersection << "\n";
            constexpr double_t radius = 0.2;
            auto sphere = Geometry::Sphere<double_t>{*intersection, radius};
            FlowMeshSphere flowMeshSphere{sphere, newFGuid()};
            m_tmpPointGuid = flowMeshSphere.getFGuid();
            m_model->add(flowMeshSphere);
        }
    }
};

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
