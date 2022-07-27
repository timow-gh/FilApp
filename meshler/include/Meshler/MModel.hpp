#ifndef MESHLER_MMODEL_HPP
#define MESHLER_MMODEL_HPP

#include <Meshler/GeometryElements/GeometryElements.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/MModelEventDispatcher.hpp>

namespace Meshler
{

class SnapGeometries;

class MModel {
    GeometryElements m_geometryElements;
    MModelEventDispatcher m_modelEventDispatcher;

  public:
    MModel() = default;
    explicit MModel(MModelEventListener* modelEventListener);

    void registerListener(MModelEventListener* modelEventListener);
    void removeListener(MModelEventListener* modelEventListener);

    template <typename TMeshlerGeometry>
    void add(const TMeshlerGeometry& meshlerGeometry)

    {
        if (m_geometryElements.add(meshlerGeometry))
            m_modelEventDispatcher.dispatchAdd(meshlerGeometry);
    }

    template <typename TGeometryElement>
    TGeometryElement* get(const FGuid& guid)
    {
        return m_geometryElements.get<TGeometryElement>(guid);
    }

    void update(const FGuid& guid);
    void remove(FGuid fGuid);
    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

    CORE_NODISCARD SnapGeometries calcModelSnapGeometries() const;
};

} // namespace Meshler

#endif // MESHLER_MMODEL_HPP
