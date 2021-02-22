#include "../Public/NodeData.hpp"
#include "../Public/Initialize.hpp"
#ifndef PROBLEM_TPP
#define PROBLEM_TPP
namespace AI
{
template <typename T>
bool Problem<T>::compare(std::shared_ptr<Node<T>> node ,std::shared_ptr<Node<T>> other)
{
    if (_problemType == ProblemType::Puzzle) {
        T otherdata   = other->getData();
        T nodedata   = node->getData();
        if (nodedata == otherdata)
            return true;
        return false;
    }
    else
    {
        
        int numqueens = 0;
       
        NodeData data = node->getData();
        int desiredqueensNum =  (int)sqrt(data._size);;
        std::cout << "DESIRED QUEENS:" << desiredqueensNum << std::endl;
         for (int i = 0; i < data._size; i++) {
            if (data._data[i]._asInt == 1)
                numqueens+=1;
        }
        if (numqueens >= desiredqueensNum)
            return true;
        return false;
    }
    
}

template <typename T>
bool  Problem<T>::CheckNode(std::shared_ptr<Node<T>> nodedata)
{
    //std::cout << "Visited states size in checknode:" << _visited_states.size() << std::endl;

    bool isIn = false;
    for (auto at= _visited_states.begin(); at!= _visited_states.end(); at++)
       if (compare(nodedata, *at)) {
           //std::cout << "they are the same" << std::endl;
            isIn = true;
       }
    if (isIn == false) {
        _visited_states.push_back(nodedata);
    }
    return isIn;
}


template <typename T>
std::list<std::shared_ptr<Node<T>>> Problem<T>::CheckNodes( std::list<std::shared_ptr<Node<T>>> nodes)
{
    std::cout << "Visited states size:" << _visited_states.size() << std::endl;
   // std::cout << "Nodes size:" << nodes.size() << std::endl;

    std::list<std::shared_ptr<Node<NodeData>>> result;
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (!CheckNode(*it)){
            result.push_back(*it);
        }
    }
    return result;
}

}
#endif