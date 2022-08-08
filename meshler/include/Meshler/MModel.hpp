#ifndef MESHLER_MMODEL_HPP
#define MESHLER_MMODEL_HPP

#include <Core/Utils/Assert.hpp>
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
    void add(TMeshlerGeometry&& meshlerGeometry)

    {
        FGuid guid = meshlerGeometry.getFGuid();
        if (m_geometryElements.add(std::forward<TMeshlerGeometry>(meshlerGeometry)))
        {
            auto* geoElem = m_geometryElements.get<TMeshlerGeometry>(guid);
            CORE_POSTCONDITION_DEBUG_ASSERT(geoElem, "geomElem not found.");
            m_modelEventDispatcher.dispatchAdd(*geoElem);
        }
    }

    template <typename TGeometryElement>
    TGeometryElement* get(const FGuid& guid)
    {
        return m_geometryElements.get<TGeometryElement>(guid);
    }

    CORE_NODISCARD SnapGeometries& getSnapGeometries()
    {
        return m_geometryElements.getSnapGeometries();
    }

    void update(const FGuid& guid);
    void remove(FGuid fGuid);
    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

    void calcModelSnapGeometries();
};

} // namespace Meshler

#endif // MESHLER_MMODEL_HPP
