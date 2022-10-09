#ifndef MESHLER_MESHLERCOMMANDS_HPP
#define MESHLER_MESHLERCOMMANDS_HPP

#include <Core/Types/THashMap.hpp>
#include <Core/Utils/Compiler.hpp>

namespace Meshler
{

enum class MeshlerCommands : std::uint32_t
{
  PLACING_INTERACTOR_SPHERE = 0,
  PLACING_INTERACTOR_CONE = 1,
  PLACING_INTERACTOR_CYLINDER = 2,
  PLACING_INTERACTOR_CUBOID = 3
};

} // namespace Meshler

namespace std
{

template <>
struct hash<Meshler::MeshlerCommands>
{
  std::size_t operator()(const Meshler::MeshlerCommands& command) const { return static_cast<std::size_t>(command); }
};

} // namespace std

#endif // MESHLER_MESHLERCOMMANDS_HPP
