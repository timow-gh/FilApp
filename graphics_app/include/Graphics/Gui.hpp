#ifndef MESHLER_GUI_HPP
#define MESHLER_GUI_HPP

#include <Graphics/Command.hpp>

namespace Graphics
{

class Gui {
public:
  virtual ~Gui();

  // Creates a sidebar button for each registered command
  virtual void registerPlacementButtonCommand(const Command& command) = 0;

  virtual void render(double timeStepInSeconds) = 0;

private:
  virtual void updateUserInterface() = 0;
};

} // namespace Graphics

#endif // MESHLER_GUI_HPP
