#include <memory>

#ifndef NODE_TPP
#define NODE_TPP
namespace AI
{
template <typename T>
std::list<std::shared_ptr<Node<T>>> Node<T>::GetChilds()
{
    return _childs;
}


template <typename T>
std::shared_ptr<Node<T>> Node<T>::GetParent()
{
    return _parent;
}


template <typename T>
bool Node<T>::HasParent()
{
    if (_parent)
        return true;
    return false;
}


template <typename T>
void Node<T>::RemoveChild(std::shared_ptr<Node<T>> node)
{
      for (auto it =_childs.begin(); it!=_childs.end(); ++it) {
          if (*it == node)
            _childs.erase(it);
      }
}


template <typename T>
void Node<T>::AddChild(std::shared_ptr<Node<T>> node)
{
    if (node)
        _childs.push_back(node);
}

template <typename T>
void Node<T>::AddParent(std::shared_ptr<Node<T>> node)
{
    if (node) {
        _parent = node;
        //node->AddChild(this);
    }
}

template <typename T>
void Node<T>::AddChilds(std::list<std::shared_ptr<Node<T>>> nodes, bool reset)
{
    if (reset) {
        nodes.erase(nodes.begin(), nodes.end());
        nodes.clear();
    }
    for (auto it = nodes.begin(); it != nodes.end(); it++)
        _childs.push_back(*it);
}

template <typename T>
void  Node<T>::setData(T data) 
{ 
    _data = data;
}

template <typename T>
std::shared_ptr<Node<T>> Node<T>::MakeNode(T data, std::shared_ptr<Node<T>> parent)
{
    std::shared_ptr<Node<T>> node(new Node<T>);
    node->setData(data);
    node->AddParent(parent);
    return node;
}

}
#endif