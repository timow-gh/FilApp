#ifndef MESHLER_GEOMETRYELEMENTBASE_HPP
#define MESHLER_GEOMETRYELEMENTBASE_HPP

#include <Core/Utils/Compiler.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

template <typename Derived>
class GeometryElementBase {
  protected:
    FGuid m_fGuid;
    bool m_isSnapGeometry{true};
    LinAl::HMatrixd m_transformation{LinAl::createIdentityHMatrix<double_t>()};

    GeometryElementBase() : m_fGuid(newFGuid()) {}

    GeometryElementBase(FGuid guid, const MGeometryConfigBase& baseConfig)
        : m_fGuid(guid)
        , m_isSnapGeometry(baseConfig.isSnapGeometry)
        , m_transformation(LinAl::createIdentityHMatrix<double_t>())
    {
    }

    GeometryElementBase(const GeometryElementBase& rhs)
        : m_fGuid(newFGuid())
        , m_isSnapGeometry(rhs.m_isSnapGeometry)
        , m_transformation(rhs.m_transformation)
    {
    }

    GeometryElementBase& operator=(const GeometryElementBase& rhs)
    {
        m_fGuid = newFGuid();
        m_isSnapGeometry = rhs.m_isSnapGeometry;
        m_transformation = rhs.m_transformation;
        return *this;
    }

    GeometryElementBase(GeometryElementBase&& rhs) CORE_NOEXCEPT
        : m_fGuid(std::move(rhs.m_fGuid))
        , m_isSnapGeometry(std::move(rhs.m_isSnapGeometry))
        , m_transformation(rhs.m_transformation)
    {
    }

    GeometryElementBase& operator=(GeometryElementBase&& rhs) CORE_NOEXCEPT
    {
        m_fGuid = std::move(rhs.m_fGuid);
        m_isSnapGeometry = std::move(rhs.m_isSnapGeometry);
        m_transformation = rhs.m_transformation;
        return *this;
    }

  public:
    CORE_NODISCARD CORE_CONSTEXPR const FGuid& getFGuid() const { return m_fGuid; }

    CORE_NODISCARD CORE_CONSTEXPR bool getIsSnapGeometry() const { return m_isSnapGeometry; }
    CORE_CONSTEXPR void setIsSnapGeometry(bool isSnapGeometry)
    {
        m_isSnapGeometry = isSnapGeometry;
    }

    CORE_NODISCARD CORE_CONSTEXPR const LinAl::HMatrixd& getTransformation() const
    {
        return m_transformation;
    }
    CORE_CONSTEXPR void setTransformation(const LinAl::HMatrixd& transformation)
    {
        m_transformation = transformation;
    }

    CORE_NODISCARD CORE_CONSTEXPR LinAl::Vec3d getPosition() const
    {
        LinAl::Vec3d result;
        LinAl::getTranslation(m_transformation, result);
        return result;
    }

    CORE_CONSTEXPR void setPosition(const LinAl::Vec3d& position)
    {
        LinAl::setTranslation(m_transformation, position);
    }

    CORE_CONSTEXPR friend bool operator==(const Derived& lhs, const Derived& rhs)
    {
        return lhs.m_fGuid == rhs.m_fGuid && lhs == rhs;
    }

    CORE_CONSTEXPR friend bool operator!=(const Derived& lhs, const Derived& rhs)
    {
        return lhs.m_fGuid == rhs.m_fGuid && !(lhs == rhs);
    }

    CORE_CONSTEXPR friend bool operator<(const Derived& lhs, const Derived& rhs)
    {
        return lhs.m_fGuid < rhs.m_fGuid;
    }
    CORE_CONSTEXPR friend bool operator>(const Derived& lhs, const Derived& rhs)
    {
        return rhs < lhs;
    }
    CORE_CONSTEXPR friend bool operator<=(const Derived& lhs, const Derived& rhs)
    {
        return !(rhs < lhs);
    }
    CORE_CONSTEXPR friend bool operator>=(const Derived& lhs, const Derived& rhs)
    {
        return !(lhs < rhs);
    }
};

} // namespace Meshler

#endif // MESHLER_GEOMETRYELEMENTBASE_HPP
