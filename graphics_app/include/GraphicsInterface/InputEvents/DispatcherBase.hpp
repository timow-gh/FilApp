#ifndef FILAPP_DISPATCHERBASE_HPP
#define FILAPP_DISPATCHERBASE_HPP

#include <vector>

namespace Graphics
{
template <typename TListener>
class DispatcherBase {
  protected:
    std::vector<TListener*> m_listener;

    template <typename TMessage>
    void dispatchImpl(const TMessage& message)
    {
        for (TListener* listener: DispatcherBase<TListener>::m_listener)
            listener->event(message);
    }

  public:
    DispatcherBase() = default;
    DispatcherBase(const DispatcherBase& dispatcherBase) = delete;
    DispatcherBase(DispatcherBase&& dispatcherBase) noexcept = delete;
    DispatcherBase& operator=(const DispatcherBase& dispatcherBase) = default;
    DispatcherBase& operator=(DispatcherBase&& dispatcherBase) noexcept = default;

    void registerListener(TListener* listener) { m_listener.push_back(listener); }

    void removeListener(TListener* listener)
    {
        auto iter = std::remove(m_listener.begin(), m_listener.end(), listener);
        if (iter != m_listener.cend())
            m_listener.erase(iter, m_listener.end());
    }
};
} // namespace Graphics

#endif // FILAPP_DISPATCHERBASE_HPP
