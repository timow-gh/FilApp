#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilAppRenderableBuffers.hpp>
#include <generated/resources/filapp_resources.h>
#include <math/vec3.h>

using namespace Graphics;

namespace FilApp
{
FilAppRenderableCreator FilAppRenderableCreator::create(filament::Engine* engine)
{
    FilAppRenderableCreator result = FilAppRenderableCreator(engine);
    result.createMaterials();
    return result;
}

FilAppRenderableCreator::FilAppRenderableCreator(filament::Engine* engine) : m_engine(engine)
{
    createMaterials();
}

static filament::Box calcFilamentBbox(const Core::TVector<Vertex>& vertices)
{
    CORE_PRECONDITION_DEBUG_ASSERT(!vertices.empty(), "Vertices are empty.");
    filament::math::float3 minVec(std::numeric_limits<float_t>::max());
    filament::math::float3 maxVec(std::numeric_limits<float_t>::lowest());
    for (const auto& vertex: vertices)
    {
        filament::math::float3 vec{vertex.position[0], vertex.position[1], vertex.position[2]};
        minVec = min(minVec, vec);
        maxVec = max(maxVec, vec);
    }
    return filament::Box().set(minVec, maxVec);
}

FilAppRenderable
FilAppRenderableCreator::createBakedColorRenderable(const Core::TVector<Vertex>& vertices,
                                                    const Core::TVector<uint16_t>& indices,
                                                    PrimitiveType primitiveType) const

{
    CORE_PRECONDITION_DEBUG_ASSERT(!vertices.empty(), "Vertices are empty.");
    CORE_PRECONDITION_DEBUG_ASSERT(!indices.empty(), "Indices are empty.");

    FilAppRenderable filAppRenderable;
    filAppRenderable.engine = m_engine;

    filAppRenderable.renderableEntity = utils::EntityManager::get().create();

    createVertexBuffer(&filAppRenderable, vertices);
    createIndicesBuffer(&filAppRenderable, indices);

    MatPair matPair;
    if (primitiveType == PrimitiveType::POINTS)
        matPair = getMaterial(FilAppMaterialType::BAKEDVERTEXCOLOR);
    else
        matPair = getMaterial(FilAppMaterialType::BAKEDFRAGCOLOR);

    filAppRenderable.mat = matPair.material;
    filAppRenderable.matInstance = matPair.matInstance;

    if (primitiveType == PrimitiveType::LINES)
        filAppRenderable.matInstance->setPolygonOffset(3.0f, 3.0f);

    bool useCulling = true;
    if (primitiveType == PrimitiveType::POINTS)
        useCulling = false;

    const std::size_t OFFSET = 0;
    filament::RenderableManager::Builder(1)
        .boundingBox(calcFilamentBbox(vertices))
        .material(0, filAppRenderable.matInstance)
        .geometry(0,
                  primitiveType,
                  filAppRenderable.vb,
                  filAppRenderable.ib,
                  OFFSET,
                  filAppRenderable.ib->getIndexCount())
        .culling(useCulling)
        .receiveShadows(false)
        .castShadows(false)
        .build(*filAppRenderable.engine, filAppRenderable.renderableEntity);

    return filAppRenderable;
}

void FilAppRenderableCreator::createMaterials()
{
    filament::Material* mat = nullptr;
    filament::MaterialInstance* matInstance = nullptr;

    mat = filament::Material::Builder()
              .package(FILAPP_RESOURCES_BAKEDVERTEXCOLOR_DATA,
                       static_cast<size_t>(FILAPP_RESOURCES_BAKEDVERTEXCOLOR_SIZE))
              .build(*m_engine);
    matInstance = mat->createInstance();
    m_filAppMaterials.emplace(FilAppMaterialType::BAKEDVERTEXCOLOR, MatPair(mat, matInstance));

    mat = filament::Material::Builder()
              .package(FILAPP_RESOURCES_BAKEDFRAGCOLOR_DATA,
                       static_cast<size_t>(FILAPP_RESOURCES_BAKEDFRAGCOLOR_SIZE))
              .build(*m_engine);
    matInstance = mat->createInstance();
    m_filAppMaterials.emplace(FilAppMaterialType::BAKEDFRAGCOLOR, MatPair(mat, matInstance));
}
const FilAppRenderableCreator::MatPair& FilAppRenderableCreator::getMaterial(
    FilAppRenderableCreator::FilAppMaterialType filAppMaterialType) const
{
    auto iter = m_filAppMaterials.find(filAppMaterialType);
    CORE_POSTCONDITION_DEBUG_ASSERT((iter != m_filAppMaterials.end()), "Material not found.");
    return iter->second;
}
void FilAppRenderableCreator::destroyMaterials()
{
    for (const auto& pair: m_filAppMaterials)
    {
        m_engine->destroy(pair.second.material);
        m_engine->destroy(pair.second.matInstance);
    }
}

} // namespace FilApp