#ifndef FILAPP_FGUIDBASE_HPP
#define FILAPP_FGUIDBASE_HPP

namespace FlowMesh
{
template <typename Derived>
class FGuidBase {
  protected:
    explicit FGuidBase(FGuid guid) : m_fGuid(guid) {}
    FGuid m_fGuid;

  public:
    [[nodiscard]] const FGuid& getFGuid() const { return m_fGuid; }

    friend bool operator<(const Derived& lhs, const Derived& rhs)
    {
        return lhs.m_fGuid < rhs.m_fGuid;
    }
    friend bool operator>(const Derived& lhs, const Derived& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator<=(const Derived& lhs, const Derived& rhs)
    {
        return !(rhs < lhs);
    }
    friend bool operator>=(const Derived& lhs, const Derived& rhs)
    {
        return !(lhs < rhs);
    }
};
}

#endif // FILAPP_FGUIDBASE_HPP
