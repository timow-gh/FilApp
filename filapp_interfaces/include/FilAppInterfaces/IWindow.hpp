#ifndef FILAPP_IWINDOW_HPP
#define FILAPP_IWINDOW_HPP

#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <vector>

namespace FilApp
{
class IView;

class IWindow {
  public:
    virtual ~IWindow() = default;

    using WindowId = uint32_t;

    virtual IView* getMainIView() = 0;
    virtual std::vector<IView*> getIViews() = 0;

    virtual WindowId getIWindowId() = 0;
};
} // namespace FilApp

#endif // FILAPP_IWINDOW_HPP
