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

    CORE_NODISCARD const GeometryElements& getGeometryElements() const
    {
        return m_geometryElements;
    }

    void registerListener(MModelEventListener* modelEventListener);
    void removeListener(MModelEventListener* modelEventListener);
    void clearListeners();

    template <typename TMeshlerGeometry>
    TMeshlerGeometry& add(TMeshlerGeometry&& meshlerGeometry)

    {
        auto& geomElem = m_geometryElements.add(std::forward<TMeshlerGeometry>(meshlerGeometry));
        m_modelEventDispatcher.dispatchAdd(geomElem);
        return geomElem;
    }
    void update(const FGuid& guid);
    void remove(FGuid fGuid);

    template <typename TGeometryElement>
    TGeometryElement* find(FGuid guid)
    {
        return m_geometryElements.find<TGeometryElement>(guid);
    }

    void updatePosition(FGuid fGuid, LinAl::Vec3d& position);
};

} // namespace Meshler

#endif // MESHLER_MMODEL_HPP
