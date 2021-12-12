#ifndef FILAPP_DISPATCHERBASE_HPP
#define FILAPP_DISPATCHERBASE_HPP

#include <vector>

namespace FilApp
{
template <typename TListener>
class DispatcherBase {
  protected:
    std::vector<TListener*> m_listener;

  public:
    void registerListener(TListener* listener)
    {
        m_listener.push_back(listener);
    }

    void removeListener(TListener* listener)
    {
        auto iter = std::remove(m_listener.begin(), m_listener.end(), listener);
        if (iter != m_listener.cend())
            m_listener.erase(iter, m_listener.end());
    }
};
} // namespace FilApp

#endif // FILAPP_DISPATCHERBASE_HPP
