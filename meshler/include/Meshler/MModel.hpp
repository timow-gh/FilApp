#ifndef MESHLER_MMODEL_HPP
#define MESHLER_MMODEL_HPP

#include <Meshler/MGuid.hpp>
#include <Meshler/MPresenter.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/GeometryElements/GeometryElements.hpp>
#include <Meshler/Interactors/SnapGeometries.hpp>
#include <Meshler/MModelEventDispatcher.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace Meshler
{

class MModel {
    GeometryElements m_geometryElements;
    MModelEventDispatcher m_modelEventDispatcher;

  public:
    MModel() = default;
    explicit MModel(MModelEventListener* modelEventListener);

    void registerListener(MModelEventListener* modelEventListener)
    {
        m_modelEventDispatcher.registerListener(modelEventListener);
    }

    void removeListener(MModelEventListener* modelEventListener)
    {
        m_modelEventDispatcher.removeListener(modelEventListener);
    }

    template <typename TMeshlerGeometry>
    void add(const TMeshlerGeometry& meshlerGeometry)
    {
        if (m_geometryElements.add(meshlerGeometry))
            m_modelEventDispatcher.dispatchAdd(meshlerGeometry);
    }

    void remove(FGuid fGuid);

    template <typename TGeometryElement>
    TGeometryElement* get(const FGuid& guid)
    {
        return m_geometryElements.get<TGeometryElement>(guid);
    }

    void update(const FGuid& guid);

    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

    CORE_NODISCARD SnapGeometries calcModelSnapGeometries() const;
};

} // namespace Meshler

#endif // MESHLER_MMODEL_HPP
