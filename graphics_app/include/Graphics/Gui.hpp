#ifndef MESHLER_GUI_HPP
#define MESHLER_GUI_HPP

namespace Graphics
{

class Gui {
public:
  virtual ~Gui();

  virtual void render(double timeStepInSeconds) = 0;

private:
  virtual void updateUserInterface() = 0;
};

} // namespace Graphics

#endif // MESHLER_GUI_HPP
