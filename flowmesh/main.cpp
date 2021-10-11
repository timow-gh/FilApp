#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FlowMesh/FlowMeshController.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>

using namespace FilApp;
using namespace FlowMesh;
using namespace Geometry;
using namespace LinAl;

int main()
{
    FilApplication::init(AppConfig(), WindowConfig());
    FilApplication& app = FilApplication::get();

    IWindow* mainWindow = app.getWindow();
    IView* mainView = mainWindow->getMainIView();

    FlowMeshController meshController;

    FlowMeshPresenter flowMeshPresenter;
    flowMeshPresenter.setMainView(mainView);

    FlowMeshModel flowMeshModel;
    flowMeshModel.setFlowMeshPresenter(&flowMeshPresenter);

    constexpr double_t RADIUS = 0.035;
    flowMeshModel.addSphere(
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 0, 0}, RADIUS),
                       xg::newGuid()));
    flowMeshModel.addSphere(
        FlowMeshSphere(Sphere<double_t>(Vec3d{1, 0, 0}, RADIUS),
                       xg::newGuid()));
    flowMeshModel.addSphere(
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 1, 0}, RADIUS),
                       xg::newGuid()));
    flowMeshModel.addSphere(
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 0, 1}, RADIUS),
                       xg::newGuid()));

    app.run();
}