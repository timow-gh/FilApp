#ifndef FILAPP_IINPUTEVENTDISPATCHER_HPP
#define FILAPP_IINPUTEVENTDISPATCHER_HPP

#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <vector>

namespace FilApp
{
class IInputEventDispatcher {
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

#endif // FILAPP_IINPUTEVENTDISPATCHER_HPP
