#ifndef MESHLER_MESHLERCOMMANDSKEYMAP_HPP
#define MESHLER_MESHLERCOMMANDSKEYMAP_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Assert.hpp>
#include <Graphics/InputEvents/KeyScancode.hpp>
#include <Meshler/Interactors/MeshlerCommands.hpp>
#include <optional>

namespace Meshler
{

class MeshlerCommandsKeyMap {
  Core::TMap<Graphics::KeyScancode, MeshlerCommands> m_keyMap;

public:
  MeshlerCommandsKeyMap() { initMap(); }

  MeshlerCommands nextInteractor(Graphics::KeyScancode keyScancode)
  {
    auto iter = m_keyMap.find(keyScancode);
    if (iter != m_keyMap.end())
      return iter->second;
    CORE_POSTCONDITION_ASSERT(false, "Key not found in map");
    return MeshlerCommands::PLACING_INTERACTOR_SPHERE;
  }

private:
  void initMap()
  {
    m_keyMap = {{Graphics::KeyScancode::SCANCODE_1, MeshlerCommands::PLACING_INTERACTOR_SPHERE},
                {Graphics::KeyScancode::SCANCODE_2, MeshlerCommands::PLACING_INTERACTOR_CONE},
                {Graphics::KeyScancode::SCANCODE_3, MeshlerCommands::PLACING_INTERACTOR_CYLINDER},
                {Graphics::KeyScancode::SCANCODE_4, MeshlerCommands::PLACING_INTERACTOR_CUBOID}};
  }
};

} // namespace Meshler

#endif // MESHLER_MESHLERCOMMANDSKEYMAP_HPP
