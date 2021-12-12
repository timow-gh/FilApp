#ifndef FILAPP_INPUTEVENTDISPATCHER_HPP
#define FILAPP_INPUTEVENTDISPATCHER_HPP

#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <vector>

namespace FilApp
{
class InputEventDispatcher {
  protected:
    std::vector<InputEventListener*> m_inputEventListener;

  public:
    void registerInputListener(InputEventListener* inputEventListener)
    {
        m_inputEventListener.push_back(inputEventListener);
    }
    void removeInputListener(InputEventListener* inputEventListener)
    {
        auto it = std::remove(m_inputEventListener.begin(),
                              m_inputEventListener.end(),
                              inputEventListener);
        m_inputEventListener.erase(it, m_inputEventListener.end());
    }
};
} // namespace FilApp

#endif // FILAPP_INPUTEVENTDISPATCHER_HPP
