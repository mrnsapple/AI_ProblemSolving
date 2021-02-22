#include <iostream>
#include "../../Public/BreadthFirstSearch/BreadthFirstSearchPuzzleLogic.hpp"
#include "../../Public/DepthFirstSearch/DepthFirstSearchAlgorithm.hpp"
namespace AI
{


std::shared_ptr<Node<NodeData>> DepthFirstSearchAlgorithm::GetNextNode(std::shared_ptr<Node<NodeData>> n)
{
    if (!n->GetParent())
        return nullptr;
    std::shared_ptr<Node<NodeData>> parent = n->GetParent();
    std::list<std::shared_ptr<Node<NodeData>>> listNodes = parent->GetChilds();  
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        if ((*it)->IsVisited == false) {
            (*it)->IsVisited = true;
            return *it;
        }
    }
    return GetNextNode(parent);
}

std::shared_ptr<Node<NodeData>> DepthFirstSearchAlgorithm::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)
{
    if (!_logic)
        return nullptr;
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    _logic->GetSuccessor(p, n);
    if (p->getUseGraphSearch())
           n->AddChilds(p->CheckNodes(listNodes), true);
    listNodes = n->GetChilds();
    if (listNodes.size() == 0) {
        return GetNextNode(n);
    }
    (*listNodes.begin())->IsVisited = true;
    return *listNodes.begin();
}
}