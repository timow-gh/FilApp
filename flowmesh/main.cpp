#include <FilApp/FilApplication.hpp>
#include <FlowMesh/FlowMesh.hpp>

int main()
{
    FilApp::FilApplication::init(FilApp::AppConfig(), FilApp::WindowConfig());

    FilApp::FilApplication& app = FilApp::FilApplication::get();

    app.run();
}