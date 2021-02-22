#include <iostream>
#include "../../Public/BreadthFirstSearch/BreadthFirstSearchPuzzleLogic.hpp"
#include "../../Public/AStar/AStarSearchAlgorithm.hpp"
#include "../../Public/Initialize.hpp"
#include "../../Public/Problem.hpp"

namespace AI
{

std::shared_ptr<Node<NodeData>> AStarSearchAlgorithm::GetParent(std::shared_ptr<Node<NodeData>> n)
{
    while (n->GetParent())
        n = n->GetParent();
    return n;
}

void  AStarSearchAlgorithm::GetNodeToUse(std::shared_ptr<Node<NodeData>> n, int f, bool increaseF)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    NodeData data = n->getData();
    if (increaseF)
        f = f + data._data[data._size]._asInt;
    else
        f =  data._data[data._size]._asInt;
    data._data[data._size+1]._asInt = f;
    n->setData(data);
    if (!(n)->unused && lower_f_node == nullptr)
        lower_f_node = n;
    if (!(n)->unused && lower_f_node) {
        NodeData lower_f_data = lower_f_node->getData();
        if ( data._data[data._size +1]._asInt <= lower_f_data._data[lower_f_data._size+1]._asInt)
            lower_f_node = n;
    }
    listNodes = n->GetChilds();
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        auto at = it;
        GetNodeToUse(*it, f, increaseF);
    }
}

int AStarSearchAlgorithm::CalculateSeparation(int a, int b, int size)
{
    int line_size = (int)sqrt(size);
    int y = 0;
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    for (int i = size-1; i >=0; i--) {
        if (i <= b && i >= a)
            y+=1;
    }
    return y;
}


void AStarSearchAlgorithm::CalculateH(std::shared_ptr<Node<NodeData>> n, std::shared_ptr<Problem<NodeData>> p)
{
    NodeData data = n->getData();
    std::shared_ptr<Node<NodeData>> desired = p->GetDesiredState();
    NodeData desired_data = desired->getData();
    int h = 0;
    if (p->GetType() == ProblemType::Puzzle)
    {
        int tiles_out_place = 0;
         for (int i = 0; i < data._size; i++) {
             if (data._data[i]._asInt != desired_data._data[i]._asInt && data._data[i]._asInt != 0)
                tiles_out_place+=1;
         }
         h=tiles_out_place;
    }
    else{
        int separation=0;
        int num_queens=0;
        for (int i = 0; i < data._size;i++)
            if (data._data[i]._asInt ==1) {
                num_queens+=1;
                for (int g = 0; g < data._size;g++) {
                    if (data._data[g]._asInt ==1 && g != i) {
                        separation += CalculateSeparation(i, g, data._size);
                    } 
                }
            }
        separation = int(float(separation)/num_queens);
        h = (int)sqrt(data._size)- num_queens;
    }
    if (h < 0)
        h = 0;
    data._data[data._size]._asInt = h;
    n->setData(data);
}

std::shared_ptr<Node<NodeData>> AStarSearchAlgorithm::GetSuccessorChilds(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;  
    n->unused = true;
    _logic->GetSuccessor((p), n);
    listNodes = n->GetChilds();
    if (p->getUseGraphSearch() && listNodes.size() > 0)
           n->AddChilds(p->CheckNodes(listNodes), true);
    listNodes = n->GetChilds();
    _numNodes+=int(listNodes.size());
    _childsNumber.push_back(int(listNodes.size()));
    for (auto it = listNodes.begin(); it != listNodes.end(); it++)
        CalculateH(*it, p);

    lower_f_node = nullptr;
    if (p->GetAlgorithmType() == AlgorithmType::AStar)
        GetNodeToUse(GetParent(n), 0, true);
    else
        GetNodeToUse(GetParent(n), 0, false);
        n = lower_f_node;
    if (n && !n->IsVisited) {
        n->IsVisited=true;
        return n;
    }
    return nullptr;
}


std::shared_ptr<Node<NodeData>> AStarSearchAlgorithm::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n) 
{
    std::cout << "IN A STAR SEARCH ALG" << std::endl;
    if (n->GetParent() == nullptr)
        CalculateH(n, p);
    if (!_logic)
        return nullptr;
    std::shared_ptr<Node<NodeData>> node;
    lower_f_node = nullptr;
    if (p->GetAlgorithmType() == AlgorithmType::AStar)
        GetNodeToUse(GetParent(n), 0, true);
    else
        GetNodeToUse(GetParent(n), 0, false); 
    n = lower_f_node;
    if (!n)
        return nullptr;
    if (!n->IsVisited ) {
        n->IsVisited=true;
        return n;
    }
    return GetSuccessorChilds( p, n);
}
}