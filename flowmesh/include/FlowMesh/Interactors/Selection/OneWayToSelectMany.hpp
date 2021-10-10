#ifndef FILAPP_ONEWAYTOSELECTMANY_HPP
#define FILAPP_ONEWAYTOSELECTMANY_HPP

namespace FlowMesh
{

// Selectable element
class M
{
};
// Collection m (set) of elements to select from
std::set<M> m;

// Index
class I
{
};
// Indices into the of set of selectable elements M
std::set<I> indices;

// The selection mapping (the set s of selected elements)
std::map<I, bool> s;

} // namespace FlowMesh

#endif // FILAPP_ONEWAYTOSELECTMANY_HPP
