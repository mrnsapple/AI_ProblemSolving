#include "../../../Public/Problems/Puzzle/PuzzleGenerator.hpp"
#include <cstdlib>
#include <iostream>
#include "../../../Public/Node.hpp"

namespace AI
{



std::shared_ptr<Node<NodeData>>  PuzzleGenerator::GetRandomInitialState(int size)
{
    std::shared_ptr<Node<NodeData>> node = GetDesiredState(size);
    NodeData nodedata = node->getData();
    int randNumOne=0;
    int randNumTwo=0;
    for (int i = 0; i < 20; i ++) {
        randNumOne = rand() % size;
        randNumTwo = rand() % size;

        for (auto it = nodedata._data.begin(); it != nodedata._data.end(); it++) {
            if ((*it)._asInt == randNumOne)
                (*it)._asInt = randNumTwo;
            else if ((*it)._asInt == randNumTwo)
                (*it)._asInt = randNumOne;
        }
    }
    // std::vector<int> pos{0,2,5,3,4,1,6,7,8};
    // for (int i = 0; i < pos.size(); i++ )
    //     nodedata._data[i]._asInt = pos[i];  
    node->setData(nodedata);
     return node;
}
std::shared_ptr<Node<NodeData>> PuzzleGenerator::AddElement(std::shared_ptr<Node<NodeData>> node)
{
    Variant var;
    var._type = Variant::TYPE_INT;
    var._asInt = 0;
    NodeData data = node->getData();
    data._data.push_back(var);
    node->setData(data);
    return node;
}

std::shared_ptr<Node<NodeData>> PuzzleGenerator::GetEmptyState(int size)
{
    NodeData nodedata;
    Variant var;
    nodedata._size = size;
    var._type = Variant::TYPE_INT;
    for (int i = 0; i < size; i++ ) {
        var._asInt = 0;        
        nodedata._data.push_back(var);
    }
    std::shared_ptr<Node<NodeData>> node = Node<NodeData>::MakeNode(nodedata);
    node->tree_lvl = 1;
    node->IsVisited=true;
    return node;
}

std::shared_ptr<Node<NodeData>>  PuzzleGenerator::GetDesiredState(int size)
{    
    NodeData nodedata;
    Variant var;
    nodedata._size = size;
    var._type = Variant::TYPE_INT;
    //std::vector<int> pos{1,2,3,8,0,4,7,6,5};
    for (int i = 0; i < size; i++ ) {
        var._asInt = i;
       // var._asInt = pos[i];
        nodedata._data.push_back(var);
    }
    std::shared_ptr<Node<NodeData>> node = Node<NodeData>::MakeNode(nodedata);
    node->tree_lvl = 1;
    node->IsVisited=true;
    return node;
}

}