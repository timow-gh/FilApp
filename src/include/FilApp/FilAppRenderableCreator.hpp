#ifndef FILAPP_FILAPPRENDERABLECREATOR_HPP
#define FILAPP_FILAPPRENDERABLECREATOR_HPP

#include <FilApp/FilAppRenderable.hpp>
#include <map>
#include <vector>

namespace FilApp
{
class FilAppRenderableCreator
{
    enum class FilAppMaterialType
    {
        BAKEDFRAGCOLOR,
        BAKEDVERTEXCOLOR
    };

    struct MatPair
    {
        filament::Material* material;
        filament::MaterialInstance* matInstance;

        MatPair(filament::Material* material,
                filament::MaterialInstance* matInstance)
            : material(material), matInstance(matInstance)
        {
        }
    };
    filament::Engine* m_engine;
    std::map<FilAppMaterialType, MatPair> m_filAppMaterials;

  public:
    using PrimitiveType = filament::RenderableManager::PrimitiveType;

    explicit FilAppRenderableCreator(filament::Engine* engine);
    ~FilAppRenderableCreator();

    FilAppRenderable
    createBakedColorRenderable(const std::vector<Vertex>& vertices,
                               const std::vector<uint16_t>& indices,
                               PrimitiveType primitiveType,
                               const filament::Box& aabb);

    FilAppRenderable
    createBakedColorRenderable(PointRenderable* pointRenderable,
                               const filament::Box& aabb);

  private:
    void createMaterials();
    [[nodiscard]] const MatPair&
    getMaterial(FilAppMaterialType filAppMaterialType) const;
};
} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLECREATOR_HPP
