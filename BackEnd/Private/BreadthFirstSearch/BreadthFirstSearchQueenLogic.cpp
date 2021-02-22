#include "../../Public/BreadthFirstSearch/BreadthFirstSearchQueenLogic.hpp"
#include "../../Public/Node.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> 
namespace AI
{

std::list<std::shared_ptr<Node<NodeData>>> BreadthFirstSearchQueenLogic::GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)
{
    std::cout << "IN QUEEN PROBLEM" << std::endl;
    std::vector<Variant> data = n->getData()._data;
    std::vector<int> Positions = GetPositionsToChange( n->getData());
    std::list<std::shared_ptr<Node<NodeData>>> listNodes = MakeNodes(n->getData(), Positions, n);
    
    if (n && listNodes.size() > 0) {
        for (auto it = listNodes.begin(); it != listNodes.end(); it++)
            (*it)->tree_lvl = n->tree_lvl+1;
        n->AddChilds(listNodes);
    }
    return listNodes;
   }

std::list<std::shared_ptr<Node<NodeData>>> BreadthFirstSearchQueenLogic::MakeNodes(NodeData nodedata,  std::vector<int> Positions, std::shared_ptr<Node<NodeData>> parent)
{
    std::list<std::shared_ptr<Node<NodeData>>> listNodes;
    NodeData  originData = nodedata;
    NodeData parentdata= parent->getData();
    NodeData parentparentdata =parent->getData();
    if (parent->GetParent())
        parentparentdata = parent->GetParent()->getData();
    for (int i = 0; i < Positions.size(); i++) {
        nodedata = originData;
        nodedata._data[Positions[i]]._asInt = 1;
        if (nodedata == parentdata  || nodedata == parentparentdata)
            std::cout << "THER ARE THE SAME" << std::endl;
        else
            listNodes.push_back(Node<NodeData>::MakeNode(nodedata, parent));
        
    }
    return listNodes;
}

int BreadthFirstSearchQueenLogic::GetYDistance(int pos, int size, int amount)
{
    int i = 0;
    int result = 0;
    for (i = i; i < size+1; i= i + amount) {
        if (pos >= i && pos < i+amount && i < size)
            return result;
        result +=1; 
        
    }

    return result;
}

int BreadthFirstSearchQueenLogic::GetXDistance(int pos, int size, int amount)
{
    int i = 0;
    for (i = 0; i < size +1; i= i + amount)
        if (pos >= i && pos < i+amount && i < size)
            return pos - i;
        
    return i;
}


bool BreadthFirstSearchQueenLogic::CheckLocation(int pos, NodeData nodedata)
{
    int line_size = (int)sqrt(nodedata._size);
    int i = 0;
    //check vertical match
    if (nodedata._data[pos]._asInt == 1)
        return false;
    for (i = pos; i > 0; i = i - line_size);
    
    for (i = i; (int)i < (int)nodedata._size; i =i + line_size) {
        
        if (i >= 0 && nodedata._data[i]._asInt != 0)
            return false;
    }
    //Check horizontal match
    for (i = 0; i < nodedata._size && i < pos; i = i + line_size);
    if (i != pos)
        i = i - line_size;
    if (i < 0)
        i = 0;
    int limit = i + line_size;
    for (i = i; (int)i < (int)limit && (int)i < (int)nodedata._size ; i++) {
    
        if (i >= 0 && i < nodedata._size && nodedata._data[i]._asInt != 0)
            return false;
    }
    //check diagonal match
    int ypos= GetYDistance(pos, nodedata._size, line_size);
    int xpos =  GetXDistance(pos, nodedata._size, line_size);
    for (int i = 0; i < nodedata._size; i++) {
        int x=0;
        int y =0;
        if (nodedata._data[i]._asInt == 1) {
            y = GetYDistance(i, nodedata._size, line_size);
            x = GetXDistance(i, nodedata._size, line_size);
            if (abs(y - ypos) == abs(x - xpos))
                return false;
        }

    }
   
    return true;

}


std::vector<int> BreadthFirstSearchQueenLogic::GetPositionsToChange(NodeData nodedata)
{
    std::vector<int> positions;
    for (int i = 0; i < nodedata._size; i++) {
        if (CheckLocation(i, nodedata))
            positions.push_back(i);
    }
    return positions;
}
}