#ifndef FILAPP_ICONTROLLER_H
#define FILAPP_ICONTROLLER_H

#include "FilApp/IInputListener.h"
#include "FilApp/IModel.h"
#include "FilApp/IView.h"
#include "FilApp/InputEvents.h"
#include <memory>

namespace FilApp
{

class IController
    : public IInputListener
{
    ~IController() override = default;
};
} // namespace FilApp

#endif // FILAPP_ICONTROLLER_H
