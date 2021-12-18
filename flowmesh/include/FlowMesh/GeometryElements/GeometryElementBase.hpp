#ifndef FILAPP_GEOMETRYELEMENTBASE_HPP
#define FILAPP_GEOMETRYELEMENTBASE_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{
template <typename Derived>
class GeometryElementBase {
  protected:
    explicit GeometryElementBase(FGuid guid)
        : m_fGuid(guid)
        , m_transformation(LinAl::createIdentityHMatrix<double_t>())
    {
    }
    FGuid m_fGuid;
    LinAl::HMatrixd m_transformation;

  public:
    [[nodiscard]] const FGuid& getFGuid() const { return m_fGuid; }
    [[nodiscard]] const LinAl::HMatrixd& getTransformation() const
    {
        return m_transformation;
    }

    void setTransformation(const LinAl::HMatrixd& transformation)
    {
        m_transformation = transformation;
    }

    CORE_NODISCARD LinAl::Vec3d getPosition() const
    {
        LinAl::Vec3d result;
        LinAl::getTranslation<double_t, 3>(m_transformation, result);
        return result;
    }

    void setPosition(const LinAl::Vec3d& position)
    {
        LinAl::setTranslation(m_transformation, position);
    }

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
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTBASE_HPP
