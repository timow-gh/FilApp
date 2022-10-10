#ifndef MESHLER_GRAPHICSCOMMANDLISTENER_HPP
#define MESHLER_GRAPHICSCOMMANDLISTENER_HPP

#include <Graphics/Command.hpp>

namespace Graphics
{
class GraphicsCommandListener {
public:
  virtual ~GraphicsCommandListener() = default;
  virtual void onCommand(const CommandId& commandId) = 0;
};
} // namespace Graphics

#endif // MESHLER_GRAPHICSCOMMANDLISTENER_HPP
