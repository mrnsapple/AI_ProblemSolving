#include <list>
#include <memory>
#ifndef NODEd_HPP
#define NODEd_HPP
namespace AI
{
template <typename T>
class Node  
{
  public: 
    std::list<std::shared_ptr<Node<T>>> GetChilds();
     std::shared_ptr<Node<T>> GetParent();
    bool HasParent();
    void RemoveChild(std::shared_ptr<Node<T>> node);
    void AddChild(std::shared_ptr<Node<T>> node);
    void AddParent(std::shared_ptr<Node<T>> node);
    void AddChilds(std::list<std::shared_ptr<Node<T>>> nodes, bool reset=false);
    void setData(T data);
    T getData() { return _data;}
    static std::shared_ptr<Node<T>> MakeNode(T data, std::shared_ptr<Node<T>> parent = nullptr);


    bool IsVisited=false;
    bool unused=false;

    int tree_lvl;

private:
    std::list<std::shared_ptr<Node<T>>> _childs;
    std::shared_ptr<Node<T>> _parent; 
    T _data;
}; 
}
#include "../Private/Node.tpp"

#endif