#ifndef FILAPP_FILAPPRENDERABLECREATOR_HPP
#define FILAPP_FILAPPRENDERABLECREATOR_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Types/TVector.hpp>
#include <FilApp/FilAppRenderable.hpp>
#include <Graphics/Vertex.hpp>

namespace FilApp
{
class FilAppRenderableCreator {
  enum class FilAppMaterialType
  {
    BAKEDFRAGCOLOR,
    BAKEDVERTEXCOLOR
  };

  struct MatPair
  {
    filament::Material* material{nullptr};
    filament::MaterialInstance* matInstance{nullptr};

    MatPair() = default;
    MatPair(filament::Material* material, filament::MaterialInstance* matInstance)
        : material(material)
        , matInstance(matInstance)
    {
    }
  };
  filament::Engine* m_engine{nullptr};
  Core::TMap<FilAppMaterialType, MatPair> m_filAppMaterials;

public:
  using PrimitiveType = filament::RenderableManager::PrimitiveType;

  static FilAppRenderableCreator create(filament::Engine* engine);

  FilAppRenderable createBakedColorRenderable(const Core::TVector<Graphics::Vertex>& vertices,
                                              const Core::TVector<uint16_t>& indices,
                                              PrimitiveType primitiveType) const;

  void destroyMaterials();

private:
  explicit FilAppRenderableCreator(filament::Engine* engine);
  void createMaterials();
  CORE_NODISCARD const MatPair& getMaterial(FilAppMaterialType filAppMaterialType) const;
};
} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLECREATOR_HPP
