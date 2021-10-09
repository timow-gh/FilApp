#include <FilApp/FilApplication.hpp>
#include <FilApp/Interfaces/IView.hpp>
#include <FilApp/Interfaces/IWindow.hpp>
#include <FlowMesh/FlowMesh.hpp>

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

    std::vector<FlowMeshSphere> spheres = {
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 0, 0}, 0.05)),
        FlowMeshSphere(Sphere<double_t>(Vec3d{1, 0, 0}, 0.05)),
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 1, 0}, 0.05)),
        FlowMeshSphere(Sphere<double_t>(Vec3d{0, 0, 1}, 0.05))};

    for (const auto& sphere: spheres)
        mainView->addRenderable(createTriangleRenderable(sphere));

    app.run();
}