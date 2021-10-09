#ifndef FILAPP_IINPUTEVENTDISPATCHER_HPP
#define FILAPP_IINPUTEVENTDISPATCHER_HPP

#include <FilApp/Interfaces/IInputListener.hpp>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT IInputEventDispatcher
{
  protected:
    std::vector<IInputListener*> m_inputEventListener;

  public:
    void registerInputListener(IInputListener* inputEventListener)
    {
        m_inputEventListener.push_back(inputEventListener);
    }
    void removeInputListener(IInputListener* inputEventListener)
    {
        auto it = std::remove(m_inputEventListener.begin(),
                              m_inputEventListener.end(),
                              inputEventListener);
        m_inputEventListener.erase(it, m_inputEventListener.end());
    }
};
} // namespace FilApp

#endif // FILAPP_IINPUTEVENTDISPATCHER_HPP
