#include <Core/Types/TArray.hpp>
#include <FilApp/FilApplication.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/MController.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/MPresenter.hpp>

using namespace Graphics;
using namespace Meshler;
using namespace Geometry;
using namespace LinAl;

void createSpheres(MModel& model)
{
  FGuid sphereToRemove;

  CORE_CONSTEXPR std::int32_t MINMAX = 1;
  CORE_CONSTEXPR double_t RADIUS = 1.0;
  CORE_CONSTEXPR double_t DIST = 4.0;
  for (std::int32_t i{-MINMAX}; i <= MINMAX; ++i)
  {
    for (std::int32_t j{-MINMAX}; j <= MINMAX; ++j)
    {
      FGuid id = newFGuid();
      if (i == 0 && j == 0)
        sphereToRemove = id;

      model.add(MSphere(Sphere<double_t>(Vec3d{static_cast<double_t>(i) * DIST, static_cast<double_t>(j) * DIST, 0}, RADIUS),
                        id,
                        MGeometryConfigBase{}));
    }
  }

  model.remove(sphereToRemove);
}

void createCones(MModel& model)
{
  // x
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0.5, 0, 0}}, 0.1), newFGuid(), MGeometryConfigBase{}));

  // y
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0.5, 0}}, 0.1), newFGuid(), MGeometryConfigBase{}));
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0.5, 0}, LinAl::Vec3d{0, 1.0, 0}}, 0.1), newFGuid(), MGeometryConfigBase{}));

  // z
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0}, LinAl::Vec3d{0, 0, 0.5}}, 0.1), newFGuid(), MGeometryConfigBase{}));
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 0.5}, LinAl::Vec3d{0, 0, 1.0}}, 0.1), newFGuid(), MGeometryConfigBase{}));
  model.add(
      MCone(Geometry::Cone<double_t>(Segment3d{LinAl::Vec3d{0, 0, 1.0}, LinAl::Vec3d{0, 0, 1.5}}, 0.1), newFGuid(), MGeometryConfigBase{}));
}

int main()
{
  Graphics::AppConfig appConfig;
  appConfig.eventPollingMode = Graphics::EventPollingMode::WAIT_EVENTS;
  appConfig.backendMode = Graphics::BackendMode::VULKAN;

  std::shared_ptr<Graphics::GraphicsApp> graphicsApp = FilApp::FilApplication::getFilApp(appConfig, WindowConfig());

  MPresenter presenter{*graphicsApp->getWindow().getMainIView()};

  MModel meshlerModel;
  meshlerModel.registerListener(&presenter);

  createSpheres(meshlerModel);
  createCones(meshlerModel);

  std::shared_ptr<MController> meshlerController = MController::create(presenter, meshlerModel);

  graphicsApp->run();
}