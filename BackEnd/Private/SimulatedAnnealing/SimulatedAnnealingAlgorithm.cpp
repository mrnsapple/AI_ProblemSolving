#include <iostream>
#include "../../Public/BreadthFirstSearch/BreadthFirstSearchPuzzleLogic.hpp"
#include "../../Public/SimulatedAnnealing/SimulatedAnnealingAlgorithm.hpp"
#include "../../Public/Initialize.hpp"
#include "../../Public/Problem.hpp"
namespace AI
{


std::shared_ptr<Node<NodeData>>   SimulatedAnnealingAlgorithm::GetNodeToUse(std::shared_ptr<Node<NodeData>> n, int f, bool useRandom)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes =  n->GetChilds();
    std::shared_ptr<Node<NodeData>> result = nullptr;
    NodeData nodedata = n->getData();
    NodeData childdata;
    for (auto it = listNodes.begin(); it != listNodes.end(); it++) {
        childdata = (*it)->getData();
        if (nodedata._data[nodedata._size]._asInt > childdata._data[childdata._size]._asInt ||
        (useRandom && (rand() % 100)/100 < exp((childdata._data[childdata._size]._asInt - nodedata._data[nodedata._size]._asInt)/temp)))
            result = (*it);

    }
    return result;
}

void SimulatedAnnealingAlgorithm::CalculateH(std::shared_ptr<Node<NodeData>> n, std::shared_ptr<Problem<NodeData>> p)
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
            if (data._data[i]._asInt ==1) 
                num_queens+=1;
        separation = int(float(separation)/num_queens);
        h = (int)sqrt(data._size)- num_queens;
    }
    if (h < 0)
        h = 0;
    data._data[data._size]._asInt = h;
    //data._data[data._size+1]._asInt = h;
    n->setData(data);
}

std::shared_ptr<Node<NodeData>> SimulatedAnnealingAlgorithm::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n) 
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;  
    temp = temp - 1;
    if (temp < 1)
        temp = 1;
    CalculateH(n, p);
    _logic->GetSuccessor((p), n);
    listNodes = n->GetChilds();
    if (p->getUseGraphSearch() && listNodes.size() > 0)
           n->AddChilds(p->CheckNodes(listNodes), true);
    listNodes = n->GetChilds();
    _numNodes+=int(listNodes.size());
    _childsNumber.push_back(int(listNodes.size()));
    for (auto it = listNodes.begin(); it != listNodes.end(); it++)
        CalculateH(*it, p);
    if (p->GetAlgorithmType() == AlgorithmType::SimulatedAnnealing)
        return  GetNodeToUse(n, 0, true);
    else
        return  GetNodeToUse(n, 0, false);
    
}
}