#include "Node.hpp"
#include "Problem.hpp"
#include <list>
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
namespace AI
{
/**
 * Containes the code with the logic about which nodes provide as next options
 **/
template <typename T>
class AlgorithmLogic
{
public:
    /**
     * returns a list of the nodes to follow the sending node
     **/
    virtual std::list<std::shared_ptr<Node<T>>> GetSuccessor(std::shared_ptr<Problem<T>> p, std::shared_ptr<Node<T>> n) { std::list<std::shared_ptr<Node<T>>>  a; 
                                                                                                                        return a;} 
};
/**
 * Containes the code with the instructions in how to  move in the tree
 **/

template <typename T>
class Algorithm
{
public:
    
    /**
     * returns a list of the node to tree is currently at
    **/
    virtual std::shared_ptr<Node<T>> GetSuccessor(std::shared_ptr<Problem<T>> p, std::shared_ptr<Node<T>> n) { return nullptr; }
    void setAlgorithmLogic(AlgorithmLogic<T> *logic ) { _logic = logic; }
    AlgorithmLogic<T> getAlgorithmLogic() { return _logic; }
    int _depth=1;
    int _numNodes = 1;
    std::vector<int> _childsNumber;
protected:
    AlgorithmLogic<T> *_logic = nullptr;
};


}
#endif