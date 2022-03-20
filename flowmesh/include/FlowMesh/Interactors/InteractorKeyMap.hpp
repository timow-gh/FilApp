#ifndef FILAPP_INTERACTORKEYMAP_HPP
#define FILAPP_INTERACTORKEYMAP_HPP

#include <FlowMesh/Interactors/InteractorCommands.hpp>
#include <GraphicsInterface/InputEvents/KeyScancode.hpp>

namespace FlowMesh
{

class InteractorKeyMap {
    std::map<Graphics::KeyScancode, InteractorCommand> m_keyMap;

  public:
    InteractorKeyMap() { initMap(); }

    std::optional<InteractorCommand> nextInteractor(Graphics::KeyScancode keyScancode)
    {
        auto iter = m_keyMap.find(keyScancode);
        if (iter != m_keyMap.end())
            return iter->second;
        return {};
    }

  private:
    void initMap()
    {
        m_keyMap = {{Graphics::KeyScancode::SCANCODE_1,
                     InteractorCommand(Command::PLACING_INTERACTOR_SPHERE)},
                    {Graphics::KeyScancode::SCANCODE_2,
                     InteractorCommand(Command::PLACING_INTERACTOR_CONE)},
                    {Graphics::KeyScancode::SCANCODE_3,
                     InteractorCommand(Command::PLACING_INTERACTOR_CYLINDER)}};
    }
};

} // namespace FlowMesh

#endif // FILAPP_INTERACTORKEYMAP_HPP
