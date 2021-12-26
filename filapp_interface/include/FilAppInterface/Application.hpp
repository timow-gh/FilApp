#ifndef FILAPP_APPLICATION_HPP
#define FILAPP_APPLICATION_HPP

#include <FilAppInterface/Window.hpp>

namespace FilApp
{
class Application {
  public:
    virtual ~Application() = default;

    virtual Window* getWindow() = 0;
};
} // namespace FilApp

#endif // FILAPP_APPLICATION_HPP
