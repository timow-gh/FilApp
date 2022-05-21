#ifndef MESHLER_INTERACTORKEYMAP_HPP
#define MESHLER_INTERACTORKEYMAP_HPP

#include <Graphics/InputEvents/KeyScancode.hpp>
#include <Meshler/Interactors/InteractorCommands.hpp>

namespace Meshler
{

class InteractorKeyMap {
    Core::TMap<Graphics::KeyScancode, InteractorCommand> m_keyMap;

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
                     InteractorCommand(Command::PLACING_INTERACTOR_CYLINDER)},
                    {Graphics::KeyScancode::SCANCODE_4,
                     InteractorCommand(Command::PLACING_INTERACTOR_CUBOID)}};
    }
};

} // namespace Meshler

#endif // MESHLER_INTERACTORKEYMAP_HPP
