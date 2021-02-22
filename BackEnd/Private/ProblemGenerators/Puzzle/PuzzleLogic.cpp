#include "../../../Public/Problems/Puzzle/PuzzleLogic.hpp"
#include "../../../Public/Node.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
namespace AI
{

std::list<std::shared_ptr<Node<NodeData>>> PuzzleLogic::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)
{

    std::vector<Variant> data = n->getData()._data;
    int EmptyCell = GetEmptyCellPosition(n);
    std::vector<int> Positions = GetPositionsToChange(n->getData()._size, EmptyCell);
    std::list<std::shared_ptr<Node<NodeData>>> listNodes = MakeNodes(n->getData(), Positions, EmptyCell -1, n);
    if (n && listNodes.size() > 0) {
        for (auto it = listNodes.begin(); it != listNodes.end(); it++)
            (*it)->tree_lvl = n->tree_lvl+1;
        std::cout << "beforeaddchilds" <<std::endl;

        n->AddChilds(listNodes);
    }
    std::cout << "get" <<std::endl;
    return listNodes;
}

std::list<std::shared_ptr<Node<NodeData>>> PuzzleLogic::MakeNodes(NodeData nodedata,  std::vector<int> Positions, int currentPos, std::shared_ptr<Node<NodeData>> parent)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    NodeData  originData = nodedata;
    NodeData parentdata= parent->getData();
    if (parent->GetParent())
        parentdata = parent->GetParent()->getData();
    for (int i = 0; i < Positions.size(); i++) {
        nodedata = originData;
        //if (nodedata._data.size() < Positions[i])
        //    continue;
        nodedata._data[currentPos]._asInt = nodedata._data[Positions[i]]._asInt;
        nodedata._data[Positions[i]]._asInt = 0;
        if (nodedata != parentdata)
            listNodes.push_back(Node<NodeData>::MakeNode(nodedata, parent));
        else
        {
            std::cout << "the same info " << std::endl;
        }
        
    }
    std::cout << "NODES LENGHT:" << listNodes.size() << std::endl;
    return listNodes;
}

int PuzzleLogic::GetEmptyCellPosition(std::shared_ptr<Node<NodeData>> n)
{
    std::vector<Variant> data = n->getData()._data;
    int i = 0;
    for (auto it = data.begin(); it != data.end(); it++, i++) {
        if ((*it)._asInt == 0)
            break;
    }
    i++;
    return i;
}

std::vector<int> PuzzleLogic::GetPositionsToChange(int size, int currentpos)
{
    std::vector<int> positions;
    int line_size = (int)sqrt(size);

  
    if  ((currentpos-1) % line_size != 0)//Not in Left Laterals
        positions.push_back(currentpos-1 -1);
    if (currentpos % line_size != 0)//Not in Right Laterals
        positions.push_back(currentpos+1 -1);
    if (currentpos + line_size <=size)
        positions.push_back(currentpos+line_size -1);
    if (currentpos - line_size > 0)
        positions.push_back(currentpos-line_size - 1);
    return positions;

}
}