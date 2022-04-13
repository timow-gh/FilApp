#include <Core/Types/TArray.hpp>
#include <FilApp/FilApplication.hpp>
#include <FlowMesh/FlowMeshController.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <FlowMesh/Model.hpp>
#include <FlowMesh/Presenter.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <GraphicsInterface/View.hpp>
#include <LinAl/LinearAlgebra.hpp>

using namespace Graphics;
using namespace FlowMesh;
using namespace Geometry;
using namespace LinAl;

void createGridSegments(Model& fMModel)
{
    Core::TVector<Geometry::Segment3d> xSegs;
    Core::TVector<Geometry::Segment3d> ySegs;
    constexpr double_t MIN = -5;
    constexpr double_t MAX = 5;
    constexpr std::size_t SEG_COUNT = static_cast<std::size_t>(MAX - MIN + 1);
    constexpr double_t LENGTH_HALF = (MAX - MIN) / 2.0;
    for (std::uint32_t i = 0; i < SEG_COUNT; ++i)
    {
        xSegs.push_back(Geometry::Segment3d{{MIN + i, -LENGTH_HALF, 0}, {MIN + i, LENGTH_HALF, 0}});
        ySegs.push_back(Geometry::Segment3d{{-LENGTH_HALF, MIN + i, 0}, {LENGTH_HALF, MIN + i, 0}});
    }
    fMModel.add(FlowMeshSegments(xSegs, newFGuid()));
    fMModel.add(FlowMeshSegments(ySegs, newFGuid()));
}

void createSpheres(Model& fMModel)
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

            fMModel.add(FlowMeshSphere(
                Sphere<double_t>(
                    Vec3d{static_cast<double_t>(i) * DIST, static_cast<double_t>(j) * DIST, 0},
                    RADIUS),
                id));
        }
    }

    fMModel.remove(sphereToRemove);
}

void createCones(Model& fmModel)
{
    // x
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0.5, 0, 0}}, 0.1),
        newFGuid()));

    // y
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0.5, 0}}, 0.1),
        newFGuid()));
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0.5, 0}, LinAl::Vec3d{0, 1.0, 0}}, 0.1),
        newFGuid()));

    // z
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0, 0.5}}, 0.1),
        newFGuid()));
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0.5}, LinAl::Vec3d{0, 0, 1.0}}, 0.1),
        newFGuid()));
    fmModel.add(FlowMeshCone(
        Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 1.0}, LinAl::Vec3d{0, 0, 1.5}}, 0.1),
        newFGuid()));
}

int main()
{
    AppConfig appConfig;
    appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;

    FilApplication::init(appConfig, WindowConfig());
    FilApplication& app = FilApplication::get();

    View* mainView = app.getWindow()->getMainIView();

    Presenter flowMeshPresenter{mainView};
    Model flowMeshModel{&flowMeshPresenter};
    FlowMeshController meshController{mainView->getInputEventDispatcher(),
                              mainView->getRayPickEventDispatcher(),
                              &flowMeshModel};
    meshController.init();

    createGridSegments(flowMeshModel);
    createSpheres(flowMeshModel);
    createCones(flowMeshModel);

    meshController.setNextInteractor(InteractorCommand(Command::PLACING_INTERACTOR_SPHERE));

    app.run();
}