#ifndef FILAPP_INTERACTOR_HPP
#define FILAPP_INTERACTOR_HPP

namespace FlowMesh
{
class Interactor {
  public:
    virtual ~Interactor() = default;

    virtual void initListeners() = 0;
};
} // namespace FlowMesh

#endif // FILAPP_INTERACTOR_HPP
