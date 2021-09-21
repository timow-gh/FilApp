#ifndef FILAPP_ICONTROLLER_HPP
#define FILAPP_ICONTROLLER_HPP

#include "IInputListener.hpp"
#include "IModel.hpp"
#include "IView.hpp"
#include "InputEvents.hpp"
#include <filapp_export.h>
#include <memory>

namespace FilApp
{
class FILAPP_EXPORT IController
    : public IInputListener
{
    ~IController() override = default;
};
} // namespace FilApp

#endif // FILAPP_ICONTROLLER_HPP
