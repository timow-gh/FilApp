#ifndef GRAPHICS_RENDEREABLEID_HPP
#define GRAPHICS_RENDEREABLEID_HPP

namespace Graphics
{
class RenderableId {
  public:
    using Type = uint32_t;

    RenderableId() noexcept = default;
    explicit RenderableId(Type type) noexcept : m_id(type) {}

    RenderableId(const RenderableId& id) noexcept = default;
    RenderableId(RenderableId&& id) noexcept = default;
    RenderableId& operator=(const RenderableId& id) noexcept = default;
    RenderableId& operator=(RenderableId&& id) noexcept = default;

    CORE_NODISCARD Type getId() const noexcept { return m_id; }

    bool operator==(const RenderableId& rhs) const noexcept { return m_id == rhs.m_id; }
    bool operator!=(const RenderableId& rhs) const noexcept { return !(rhs == *this); }
    bool operator<(const RenderableId& rhs) const noexcept { return m_id < rhs.m_id; }
    bool operator>(const RenderableId& rhs) const noexcept { return rhs < *this; }
    bool operator<=(const RenderableId& rhs) const noexcept { return !(rhs < *this); }
    bool operator>=(const RenderableId& rhs) const noexcept { return !(*this < rhs); }

  private:
    Type m_id{0};
};
} // namespace Graphics

namespace std
{

template <>
struct hash<Graphics::RenderableId>
{
    std::size_t operator()(Graphics::RenderableId id) { return id.getId(); }
};

} // namespace std

#endif // GRAPHICS_RENDEREABLEID_HPP
