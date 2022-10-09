#ifndef MESHLER_COMMAND_HPP
#define MESHLER_COMMAND_HPP

#include <Core/Types/TString.hpp>
#include <Core/Utils/Compiler.hpp>
#include <cstdint>
#include <functional>
#include <utility>

namespace Graphics
{

class CommandId {
  std::uint32_t m_id{0};

public:
  CORE_CONSTEXPR CommandId() = default;
  CORE_CONSTEXPR explicit CommandId(std::uint32_t id)
      : m_id(id)
  {
  }

  CORE_NODISCARD CORE_CONSTEXPR std::uint32_t id() const { return m_id; }

  CORE_CONSTEXPR bool operator==(const CommandId& other) const { return m_id == other.m_id; }
  CORE_CONSTEXPR bool operator!=(const CommandId& other) const { return m_id != other.m_id; }

  CORE_CONSTEXPR bool operator<(const CommandId& rhs) const { return m_id < rhs.m_id; }
  CORE_CONSTEXPR bool operator>(const CommandId& rhs) const { return rhs < *this; }
  CORE_CONSTEXPR bool operator<=(const CommandId& rhs) const { return !(rhs < *this); }
  CORE_CONSTEXPR bool operator>=(const CommandId& rhs) const { return !(*this < rhs); }
};

class Command {
public:
  using CommandIdCallBack = std::function<void(CommandId)>;

  Command(const CommandId& id, Core::TString name, CommandIdCallBack callback)
      : m_id(id)
      , m_name(std::move(name))
      , m_callback(std::move(callback))
  {
  }

  CORE_NODISCARD const CommandId& getId() const { return m_id; }
  CORE_NODISCARD const Core::TString& getName() const { return m_name; }
  CORE_NODISCARD const CommandIdCallBack& getCallback() const { return m_callback; }

  bool operator==(const Command& rhs) const { return m_id == rhs.m_id; }
  bool operator!=(const Command& rhs) const { return !(rhs == *this); }

  bool operator<(const Command& rhs) const { return m_id < rhs.m_id; }
  bool operator>(const Command& rhs) const { return rhs < *this; }
  bool operator<=(const Command& rhs) const { return !(rhs < *this); }
  bool operator>=(const Command& rhs) const { return !(*this < rhs); }

private:
  CommandId m_id;
  Core::TString m_name;
  CommandIdCallBack m_callback;
};

} // namespace Graphics

#endif // MESHLER_COMMAND_HPP
