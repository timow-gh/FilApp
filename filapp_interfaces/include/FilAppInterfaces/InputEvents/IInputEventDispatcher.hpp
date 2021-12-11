#ifndef FILAPP_IINPUTEVENTDISPATCHER_HPP
#define FILAPP_IINPUTEVENTDISPATCHER_HPP

#include <FilAppInterfaces/InputEvents/IInputEventListener.hpp>
#include <vector>

namespace FilApp
{
class IInputEventDispatcher {
  protected:
    std::vector<IInputEventListener*> m_inputEventListener;

  public:
    void registerInputListener(IInputEventListener* inputEventListener)
    {
        m_inputEventListener.push_back(inputEventListener);
    }
    void removeInputListener(IInputEventListener* inputEventListener)
    {
        auto it = std::remove(m_inputEventListener.begin(),
                              m_inputEventListener.end(),
                              inputEventListener);
        m_inputEventListener.erase(it, m_inputEventListener.end());
    }
};
} // namespace FilApp

#endif // FILAPP_IINPUTEVENTDISPATCHER_HPP
