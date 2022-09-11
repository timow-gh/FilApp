#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/MPresenter.hpp>

namespace Meshler
{
MModel::MModel(MModelEventListener* modelEventListener)
{
  m_modelEventDispatcher.registerListener(modelEventListener);
}
void MModel::registerListener(MModelEventListener* modelEventListener)
{
  m_modelEventDispatcher.registerListener(modelEventListener);
}
void MModel::removeListener(MModelEventListener* modelEventListener)
{
  m_modelEventDispatcher.removeListener(modelEventListener);
}
void MModel::clearListeners()
{
  m_modelEventDispatcher.clearListeners();
}
void MModel::update(const FGuid& guid)
{
  // clang-format off
    if (auto elem = find<MCone>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = find<MCuboid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = find<MCylinder>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = find<MGrid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = find<MSegments>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = find<MSphere>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
  // clang-format on
}
void MModel::remove(FGuid fGuid)
{
  m_geometryElements.remove(fGuid);
  m_modelEventDispatcher.dispatchRemove(fGuid);
}
void MModel::updatePosition(FGuid fGuid, LinAl::Vec3d& position)
{
  m_geometryElements.updatePosition(fGuid, position);
  m_modelEventDispatcher.dispatchPositionChanged(PositionEvent{fGuid, position});
}

} // namespace Meshler
