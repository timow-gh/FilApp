#include "FilAppRenderable.hpp"
#include "FilAppRenderableBuffers.hpp"
#include "generated/resources/filapp_resources.h"
#include "math/vec3.h"

namespace FilApp
{
filament::Box calcFilamentBbox(const std::vector<Vertex>& vertices)
{
    filament::math::float3 minVec(std::numeric_limits<float>::max());
    filament::math::float3 maxVec(std::numeric_limits<float>::lowest());
    for (const auto& vertex: vertices)
    {
        filament::math::float3 vec{vertex.position[0],
                                   vertex.position[1],
                                   vertex.position[2]};
        minVec = min(minVec, vec);
        maxVec = max(maxVec, vec);
    }
    return filament::Box().set(minVec, maxVec);
}

FilAppRenderable createBakedColorRenderable(
    const std::vector<Vertex>& vertices,
    const std::vector<uint16_t>& indices,
    filament::RenderableManager::PrimitiveType primitiveType,
    const filament::Box& aabb,
    filament::Engine* engine)
{
    FilAppRenderable filAppRenderable;
    filAppRenderable.engine = engine;

    filAppRenderable.renderableEntity = utils::EntityManager::get().create();

    createVertexBuffer(&filAppRenderable, vertices);
    createIndicesBuffer(&filAppRenderable, indices);

    filAppRenderable.mat = filament::Material::Builder()
                               .package(FILAPP_RESOURCES_BAKEDFRAGCOLOR_DATA,
                                        FILAPP_RESOURCES_BAKEDFRAGCOLOR_SIZE)
                               .build(*filAppRenderable.engine);

    const std::size_t OFFSET = 0;
    filament::RenderableManager::Builder(1)
        .boundingBox(calcFilamentBbox(vertices))
        .material(0, filAppRenderable.mat->getDefaultInstance())
        .geometry(0,
                  primitiveType,
                  filAppRenderable.vb,
                  filAppRenderable.ib,
                  OFFSET,
                  filAppRenderable.ib->getIndexCount())
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*filAppRenderable.engine, filAppRenderable.renderableEntity);

    return filAppRenderable;
}

FilAppRenderable createBakedColorRenderable(PointRenderable* pointRenderable,
                                            const filament::Box& aabb,
                                            filament::Engine* engine)
{
    FilAppRenderable filAppRenderable;
    filAppRenderable.engine = engine;

    constexpr std::size_t VERTEX_SIZE = sizeof(Vertex);
    createVertexBuffer(&filAppRenderable, pointRenderable, VERTEX_SIZE);
    createIndicesBuffer(&filAppRenderable, pointRenderable->getIndices());

    filAppRenderable.mat = filament::Material::Builder()
                               .package(FILAPP_RESOURCES_BAKEDVERTEXCOLOR_DATA,
                                        FILAPP_RESOURCES_BAKEDVERTEXCOLOR_SIZE)
                               .build(*engine);

    filAppRenderable.renderableEntity = utils::EntityManager::get().create();
    filAppRenderable.matInstance = filAppRenderable.mat->createInstance();

    filament::RenderableManager::Builder(1)
        .boundingBox(aabb)
        .material(0, filAppRenderable.matInstance)
        .geometry(0,
                  filament::RenderableManager::PrimitiveType::POINTS,
                  filAppRenderable.vb,
                  filAppRenderable.ib,
                  0,
                  filAppRenderable.ib->getIndexCount())
        .culling(false)
        .receiveShadows(false)
        .castShadows(false)
        .build(*engine, filAppRenderable.renderableEntity);

    return filAppRenderable;
}
} // namespace FilApp
