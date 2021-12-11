#ifndef FILAPP_RENDEREABLEID_HPP
#define FILAPP_RENDEREABLEID_HPP

namespace FilApp
{
class RenderableId {
  public:
    using Type = uint32_t;

    RenderableId() noexcept = default;
    RenderableId(Type type) noexcept : m_id(type) {}

    RenderableId(const RenderableId& id) noexcept = default;
    RenderableId(RenderableId&& id) noexcept = default;
    RenderableId& operator=(const RenderableId& id) noexcept = default;
    RenderableId& operator=(RenderableId&& id) noexcept = default;

    [[nodiscard]] Type getId() const noexcept { return m_id; }

    bool operator==(const RenderableId& rhs) const noexcept
    {
        return m_id == rhs.m_id;
    }
    bool operator!=(const RenderableId& rhs) const noexcept
    {
        return !(rhs == *this);
    }

    bool operator<(const RenderableId& rhs) const noexcept
    {
        return m_id < rhs.m_id;
    }
    bool operator>(const RenderableId& rhs) const noexcept
    {
        return rhs < *this;
    }
    bool operator<=(const RenderableId& rhs) const noexcept
    {
        return !(rhs < *this);
    }
    bool operator>=(const RenderableId& rhs) const noexcept
    {
        return !(*this < rhs);
    }

  private:
    Type m_id{0};
};
} // namespace FilApp

namespace std
{

template <>
struct hash<FilApp::RenderableId>
{
    std::size_t operator()(FilApp::RenderableId id) { return id.getId(); }
};

} // namespace std

#endif // FILAPP_RENDEREABLEID_HPP
