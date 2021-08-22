#include <Application.h>

int main(int argc, char** argv)
{
    FilApp::Application& app = FilApp::Application::get();
    app.run(FilApp::WindowConfig());
    return 0;
}
