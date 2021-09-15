#ifndef FILAPP_ICONTROLLER_HPP
#define FILAPP_ICONTROLLER_HPP

#include "FilApp/IInputListener.hpp"
#include "FilApp/IModel.hpp"
#include "FilApp/IView.hpp"
#include "FilApp/InputEvents.hpp"
#include <memory>
#include <filapp_export.h>

namespace FilApp
{

class FILAPP_EXPORT IController
    : public IInputListener
{
    ~IController() override = default;
};
} // namespace FilApp

#endif // FILAPP_ICONTROLLER_HPP
