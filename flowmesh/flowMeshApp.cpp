#include <Core/Types/TArray.hpp>
#include <FilApp/FilApplication.hpp>
#include <FlowMesh/FlowMeshController.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGrid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

using namespace Graphics;
using namespace FlowMesh;
using namespace Geometry;
using namespace LinAl;

void createSpheres(FlowMeshModel& model)
{
    FGuid sphereToRemove;

    constexpr std::int32_t MINMAX = 1;
    constexpr double_t RADIUS = 1.0;
    constexpr double_t DIST = 4.0;
    for (std::int32_t i{-MINMAX}; i <= MINMAX; ++i)
    {
        for (std::int32_t j{-MINMAX}; j <= MINMAX; ++j)
        {
            FGuid id = newFGuid();
            if (i == 0 && j == 0)
                sphereToRemove = id;

            model.add(FlowMeshSphere(
                Sphere<double_t>(
                    Vec3d{static_cast<double_t>(i) * DIST, static_cast<double_t>(j) * DIST, 0},
                    RADIUS),
                id,
                FlowMeshGeometryConfigBase{}));
        }
    }

    model.remove(sphereToRemove);
}

void createCones(FlowMeshModel& model)
{
    // x
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0.5, 0, 0}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));

    // y
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0.5, 0}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0.5, 0}, LinAl::Vec3d{0, 1.0, 0}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));

    // z
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0, 0.5}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0.5}, LinAl::Vec3d{0, 0, 1.0}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));
    model.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 1.0}, LinAl::Vec3d{0, 0, 1.5}}, 0.1),
        newFGuid(),
        FlowMeshGeometryConfigBase{}));
}

int main()
{
    AppConfig appConfig;
    appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;
    appConfig.backendMode = Graphics::BackendMode::VULKAN;

    std::shared_ptr<Graphics::GraphicsApp> graphicsApp =
        FilApplication::getFilApp(appConfig, WindowConfig());

    FlowMeshPresenter flowMeshPresenter{graphicsApp->getWindow().getMainIView()};

    FlowMeshModel flowMeshModel;
    flowMeshModel.registerListener(&flowMeshPresenter);

    createSpheres(flowMeshModel);
    createCones(flowMeshModel);

    std::shared_ptr<FlowMeshController> flowMeshController =
        FlowMeshController::create(&flowMeshPresenter, &flowMeshModel);

    graphicsApp->run();
}