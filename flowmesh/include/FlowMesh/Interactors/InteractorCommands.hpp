#ifndef FILAPP_INTERACTORCOMMANDS_HPP
#define FILAPP_INTERACTORCOMMANDS_HPP

#include <Core/Types/THashMap.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/PlacingInteractor.hpp>
#include <GraphicsInterface/InputEvents/KeyEvent.hpp>
#include <GraphicsInterface/InputEvents/KeyScancode.hpp>

namespace FlowMesh
{

enum class Command : std::uint32_t
{
    PLACING_INTERACTOR_SPHERE = 0,
    PLACING_INTERACTOR_CONE = 1,
    PLACING_INTERACTOR_CYLINDER = 2
};

class InteractorCommand {
    Command m_id;

  public:
    InteractorCommand() : m_id(Command::PLACING_INTERACTOR_SPHERE) {}
    explicit InteractorCommand(Command id) : m_id(id) {}

    bool operator<(const InteractorCommand& rhs) const { return m_id < rhs.m_id; }
    bool operator>(const InteractorCommand& rhs) const { return rhs < *this; }
    bool operator<=(const InteractorCommand& rhs) const { return !(rhs < *this); }
    bool operator>=(const InteractorCommand& rhs) const { return !(*this < rhs); }

    CORE_NODISCARD Command getId() const { return m_id; }
};

} // namespace FlowMesh

namespace std
{

template <>
struct hash<FlowMesh::InteractorCommand>
{
    std::size_t operator()(const FlowMesh::InteractorCommand& command) const
    {
        return static_cast<std::size_t>(command.getId());
    }
};

} // namespace std

#endif // FILAPP_INTERACTORCOMMANDS_HPP
