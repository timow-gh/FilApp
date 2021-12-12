#ifndef FILAPP_PICKINGINTERACTOR_HPP
#define FILAPP_PICKINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <FilAppInterfaces/InputEvents/PickRayEvent.hpp>
#include <FilAppInterfaces/InputEvents/PickRayMoveEvent.hpp>
#include <FilAppInterfaces/InputEvents/RayPickEventListener.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>

namespace FlowMesh
{
class PickingInteractor : public Interactor {
    FlowMesh::FlowMeshModel* m_model;

  public:
    explicit PickingInteractor(FlowMeshModel* model) : m_model(model) {}

  private:
    void event(const FilApp::PickRayEvent& pickRayEvent) override
    {
        std::cout << "PickRayEvent: (" << pickRayEvent.origin[0] << ", "
                  << pickRayEvent.origin[1] << ", " << pickRayEvent.origin[2]
                  << "), (" << pickRayEvent.direction[0] << ", "
                  << pickRayEvent.direction[1] << ", "
                  << pickRayEvent.direction[2] << ")\n";
    }
    void event(const FilApp::PickRayMoveEvent& pickRayMoveEvent) override
    {
        std::cout << "PickRayMoveEvent: (" << pickRayMoveEvent.origin[0] << ", "
                  << pickRayMoveEvent.origin[1] << ", "
                  << pickRayMoveEvent.origin[2] << "), ("
                  << pickRayMoveEvent.direction[0] << ", "
                  << pickRayMoveEvent.direction[1] << ", "
                  << pickRayMoveEvent.direction[2] << ")\n";
    }
};

} // namespace FlowMesh

#endif // FILAPP_PICKINGINTERACTOR_HPP
