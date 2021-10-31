#include <Core/Types/TArray.hpp>
#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FlowMesh/FlowMeshController.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/FlowMeshSegments.hpp>
#include <FlowMesh/FlowMeshSphere.hpp>
#include <Geometry/Segment.hpp>

using namespace FilApp;
using namespace FlowMesh;
using namespace Geometry;
using namespace LinAl;

int main()
{
    AppConfig appConfig{};
    appConfig.backendMode = BackendMode::OPENGL;

    FilApplication::init(appConfig, WindowConfig());
    FilApplication& app = FilApplication::get();

    IWindow* mainWindow = app.getWindow();
    IView* mainView = mainWindow->getMainIView();

    FlowMeshController meshController;

    FlowMeshPresenter flowMeshPresenter;
    flowMeshPresenter.setMainView(mainView);

    FlowMeshModel flowMeshModel;
    flowMeshModel.setFlowMeshPresenter(&flowMeshPresenter);

    Core::TVector<Geometry::Segment3d> xSegs;
    Core::TVector<Geometry::Segment3d> ySegs;
    constexpr int32_t MIN = -5;
    constexpr int32_t MAX = 5;
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
    flowMeshModel.addSegments(FlowMeshSegments(xSegs, xg::newGuid()));
    flowMeshModel.addSegments(FlowMeshSegments(ySegs, xg::newGuid()));

    constexpr int32_t MINMAX = 1;
    constexpr double_t RADIUS = 0.5;
    constexpr double_t DIST = 1.5;
    for (int32_t i{-MINMAX}; i <= MINMAX; ++i)
        for (int32_t j{-MINMAX}; j <= MINMAX; ++j)
            flowMeshModel.addSphere(FlowMeshSphere(
                Sphere<double_t>(Vec3d{static_cast<double>(i) * DIST,
                                       static_cast<double>(j) * DIST,
                                       0},
                                 RADIUS),
                xg::newGuid()));

    app.run();
}