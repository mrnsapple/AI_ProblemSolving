#include <iostream>
#include "../../Public/BreadthFirstSearch/BreadthFirstSearchPuzzleLogic.hpp"
#include "../../Public/BreadthFirstSearch/BreadthFirstSearchAlgorithm.hpp"
namespace AI
{

std::shared_ptr<Node<NodeData>> BreadthFirstSearchAlgorithm::GetParent(std::shared_ptr<Node<NodeData>> n)
{
    while (n->GetParent())
        n = n->GetParent();
    return n;
}

std::shared_ptr<Node<NodeData>> BreadthFirstSearchAlgorithm::GetFirstNodeFromNextLvl(std::shared_ptr<Node<NodeData>> n)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    std::shared_ptr<Node<NodeData>> node;
    if (!(n)->unused)
        return n;
    listNodes = n->GetChilds();
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        auto node = GetFirstNodeFromNextLvl(*it);
        if (node)
            return node;
    }
    return nullptr;

}

std::shared_ptr<Node<NodeData>> BreadthFirstSearchAlgorithm::GetFirstNodeFromLvl(std::shared_ptr<Node<NodeData>> n)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    std::shared_ptr<Node<NodeData>> node;
    if (n->tree_lvl > _depth || (n->tree_lvl == _depth && (n)->IsVisited))
        return nullptr;
    if (!(n)->IsVisited || !n->unused)
        return n;
    listNodes = n->GetChilds();
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        auto node = GetFirstNodeFromLvl(*it);
        if (node)
            return node;
    }
    return nullptr;
}

std::shared_ptr<Node<NodeData>> BreadthFirstSearchAlgorithm::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n) 
{ 
    if (!_logic)
        return nullptr;
    auto node   = GetFirstNodeFromLvl(GetParent(n));
    if (!node)
        n = GetFirstNodeFromNextLvl(GetParent(n));
    else
        n = node;
    if (!n)
        return nullptr;
    if (!n->IsVisited) {
        n->IsVisited=true;
        return n;
    }


    std::list<std::shared_ptr<Node<NodeData>>> listNodes;  
    BreadthFirstSearchPuzzleLogic *log = (BreadthFirstSearchPuzzleLogic *)_logic;
    n->unused = true;
    _logic->GetSuccessor(p, n);
    if (p->getUseGraphSearch())
           n->AddChilds(p->CheckNodes(listNodes), true);
    listNodes = n->GetChilds();
    if (listNodes.size() == 0)
        return GetSuccessor(p, n);
    _numNodes+=int(listNodes.size());
    _childsNumber.push_back(int(listNodes.size()));
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        NodeData data= (*it)->getData();
        if (!(*it)->IsVisited) {
            (*it)->IsVisited = true;
            return (*it);
        }    
    }
    return nullptr;
}
}