#ifndef MESHLER_GEOMELEMENTCONTAINER_HPP
#define MESHLER_GEOMELEMENTCONTAINER_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/GeometryElements/SnapGeometries.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

template <typename TGeomElement>
class GeomElementContainer {
    Core::TVector<TGeomElement> m_elements;

  public:
    using type_name = TGeomElement;
    using size_type = typename Core::TVector<TGeomElement>::size_type;
    using iterator = typename Core::TVector<TGeomElement>::iterator;
    using const_iterator = typename Core::TVector<TGeomElement>::const_iterator;
    using reverse_iterator = typename Core::TVector<TGeomElement>::reverse_iterator;
    using const_reverse_iterator = typename Core::TVector<TGeomElement>::const_reverse_iterator;
    using reference = typename Core::TVector<TGeomElement>::reference;
    using const_reference = typename Core::TVector<TGeomElement>::const_reference;

    size_type size() const { return m_elements.size(); }
    CORE_NODISCARD bool empty() const { return m_elements.empty(); }
    CORE_NODISCARD bool contains(FGuid guid) const
    {
        return std::find_if(cbegin(),
                            cend(),
                            [&guid](const TGeomElement& element)
                            {
                                return element.getFGuid() == guid;
                            }) != cend();
    }

    TGeomElement& add(TGeomElement&& element)
    {
        m_elements.push_back(std::forward<TGeomElement>(element));
        return m_elements.back();
    }

    // Deletes the element with the given guid and returns true if the element was found and
    // deleted. Otherwise, returns false. Runs in O(n) time.
    bool remove(FGuid guid)
    {
        auto iter = std::find_if(begin(),
                                 end(),
                                 [&guid](const TGeomElement& element)
                                 {
                                     return element.getFGuid() == guid;
                                 });
        if (iter != m_elements.end())
        {
            m_elements.erase(iter);
            return true;
        }
        return false;
    }

    TGeomElement* find(FGuid guid)
    {
        auto iter = std::find_if(begin(),
                                 end(),
                                 [&guid](const TGeomElement& element)
                                 {
                                     return element.getFGuid() == guid;
                                 });
        if (iter != m_elements.end())
            return &(*iter);
        return nullptr;
    }

    iterator begin() { return m_elements.begin(); }
    iterator end() { return m_elements.end(); }

    const_iterator begin() const { return m_elements.begin(); }
    const_iterator end() const { return m_elements.end(); }

    const_iterator cbegin() const { return m_elements.cbegin(); }
    const_iterator cend() const { return m_elements.cend(); }

    reverse_iterator rbegin() { return m_elements.rbegin(); }
    reverse_iterator rend() { return m_elements.rend(); }

    [[nodiscard]] const_reverse_iterator rbegin() const { return m_elements.rbegin(); }
    const_reverse_iterator rend() const { return m_elements.rend(); }

    const_reverse_iterator crbegin() const { return m_elements.crbegin(); }
    const_reverse_iterator crend() const { return m_elements.crend(); }
};

} // namespace Meshler

#endif // MESHLER_GEOMELEMENTCONTAINER_HPP
