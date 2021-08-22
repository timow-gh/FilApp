#include <Application.h>

int main(int argc, char** argv)
{
    FilApp::AppConfig appConfig;
    FilApp::Application::init(appConfig);
    FilApp::Application::get().run(FilApp::WindowConfig());
    return 0;
}
