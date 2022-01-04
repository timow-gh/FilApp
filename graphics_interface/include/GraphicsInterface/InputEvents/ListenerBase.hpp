#ifndef FILAPP_LISTENER_HPP
#define FILAPP_LISTENER_HPP

namespace Graphics
{
class ListenerBase {
  public:
    virtual ~ListenerBase() = default;

    ListenerBase(const ListenerBase& listener) = delete;
    ListenerBase& operator=(const ListenerBase& listener) = delete;
    ListenerBase(ListenerBase&& listener) = default;
    ListenerBase& operator=(ListenerBase&& listener) = default;
};
} // namespace Graphics

#endif // FILAPP_LISTENER_HPP
