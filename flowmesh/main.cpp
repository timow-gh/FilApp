#include <Core/Types/TArray.hpp>
#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FlowMesh/FlowMeshController.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/FlowMeshSegments.hpp>
#include <FlowMesh/FlowMeshSphere.hpp>
#include <Geometry/Cone.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

using namespace FilApp;
using namespace FlowMesh;
using namespace Geometry;
using namespace LinAl;

void createGridSegments(FlowMeshModel& fMModel)
{
    Core::TVector<Geometry::Segment3d> xSegs;
    Core::TVector<Geometry::Segment3d> ySegs;
    constexpr int32_t MIN = -8;
    constexpr int32_t MAX = 8;
    constexpr std::size_t SEG_COUNT = MAX - MIN + 1;
    constexpr double_t LENGTH_HALF = static_cast<double_t>(MAX - MIN) / 2.0;
    for (int32_t i = 0; i < SEG_COUNT; ++i)
    {
        xSegs.push_back(Geometry::Segment3d{
            {static_cast<double>(MIN + i), -LENGTH_HALF, 0},
            {static_cast<double>(MIN + i), LENGTH_HALF, 0}});
        ySegs.push_back(Geometry::Segment3d{
            {-LENGTH_HALF, static_cast<double>(MIN + i), 0},
            {LENGTH_HALF, static_cast<double>(MIN + i), 0}});
    }
    fMModel.addSegments(FlowMeshSegments(xSegs, newTypeId()));
    fMModel.addSegments(FlowMeshSegments(ySegs, newTypeId()));
}

void createSpheres(FlowMeshModel& fMModel)
{
    TypeId sphereToRemove;

    constexpr int32_t MINMAX = 1;
    constexpr double_t RADIUS = 0.5;
    constexpr double_t DIST = 1.5;
    for (int32_t i{-MINMAX}; i <= MINMAX; ++i)
    {
        for (int32_t j{-MINMAX}; j <= MINMAX; ++j)
        {
            TypeId id = newTypeId();
            if (i == 0 && j == 0)
                sphereToRemove = id;

            fMModel.addSphere(FlowMeshSphere(
                Sphere<double_t>(Vec3d{static_cast<double>(i) * DIST,
                                       static_cast<double>(j) * DIST,
                                       0},
                                 RADIUS),
                id));
        }
    }

    fMModel.remove(sphereToRemove);
}

void createCones(FlowMeshModel& fmModel)
{
    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0.5, 0, 0}},
            0.1),
        newTypeId()));

    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0.5, 0}},
            0.1),
        newTypeId()));
    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0.5, 0}, LinAl::Vec3d{0, 1.0, 0}},
            0.1),
        newTypeId()));

    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0, 0.5}},
            0.1),
        newTypeId()));
    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0, 0.5}, LinAl::Vec3d{0, 0, 1.0}},
            0.1),
        newTypeId()));
    fmModel.addCone(FlowMeshCone(
        Geometry::Cone<double_t>(
            Segment3d{LinAl::Vec3d{0, 0, 1.0}, LinAl::Vec3d{0, 0, 1.5}},
            0.1),
        newTypeId()));
}

int main()
{
    AppConfig appConfig{};
    appConfig.backendMode = BackendMode::OPENGL;
    appConfig.eventPollingMode = EventPollingMode::WAIT_EVENTS;

    FilApplication::init(appConfig, WindowConfig());
    FilApplication& app = FilApplication::get();

    IWindow* mainWindow = app.getWindow();
    IView* mainView = mainWindow->getMainIView();

    FlowMeshController meshController;

    FlowMeshPresenter flowMeshPresenter;
    flowMeshPresenter.setMainView(mainView);

    FlowMeshModel flowMeshModel;
    flowMeshModel.setFlowMeshPresenter(&flowMeshPresenter);

    createGridSegments(flowMeshModel);
    createSpheres(flowMeshModel);
    createCones(flowMeshModel);

    //    flowMeshPresenter.setIdleAnimation(FilApp::Vec3{0, 1, 0});
    app.run();
}