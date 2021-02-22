#include <memory>
#include "../Public/Node.hpp"
#include "../Public/Problem.hpp"
#include "../Public/Algorithm.hpp"
//#include "Utilities.cpp"
//#include "../../main.cpp"

#ifndef TREE_TPP
#define TREE_TPP
namespace AI
{



template <typename T>
#ifdef ONLY_BACK
std::shared_ptr<Node<T>>  Tree<T>::Tree_Search(std::shared_ptr<Problem<T>> &p, std::unique_ptr<Algorithm<T>> &al)
#else
std::shared_ptr<Node<T>>  Tree<T>::Tree_Search(std::shared_ptr<Problem<T>> &p, std::unique_ptr<Algorithm<T>> &al, WorkerThread *wind)
#endif
{
    std::shared_ptr<Node<T>> n = p->GetInitialState();
    std::shared_ptr<Node<T>> desired = p->GetDesiredState();
    #ifndef ONLY_BACK
    if (wind && p && p->GetType() == ProblemType::Puzzle && desired) {
        wind->getState(desired->getData(), al->_depth, al->_numNodes,al->_childsNumber,false);
        wind->getState(n->getData(), al->_depth, al->_numNodes, al->_childsNumber);
        wind->_reset = false;
    }
    #endif
    
    while (n) { 
        if (p->compare(n, desired)) break;
        n =  al->GetSuccessor(p, n);
        std::cout <<std::endl<< "IN LOOP:"<<std::endl;
        if (!n) break;
        if ( (int)al->_depth < (int)n->tree_lvl)
            al->_depth = n->tree_lvl;
        std::cout << "DEPTH:" << n->tree_lvl << std::endl;
        std::cout << "AL DEPTH:" << al->_depth << std::endl;
        #ifndef ONLY_BACK
        if (wind) {
            wind->LoopPauseGame();
            wind->getState(n->getData(), al->_depth, al->_numNodes, al->_childsNumber);
             if (wind->_reset) break;
       }
        #endif
        NodeData data = n->getData();
        std::vector<Variant> datav = data._data;
        int i = 0;
        for (auto it = datav.begin(); it != datav.end(); it++) {
            if (i % (int)sqrt( (int)data._size) == 0) {
                std::cout << std::endl;
            }
            i++;    
            std::cout << (*it)._asInt;
            std::cout << ",";
        
        }
        // ///
        std::cout <<std::endl<< "End LOOP:"<<std::endl;

    }
    std::cout << "OUT OF LOOP BABY" << std::endl;
    #ifndef ONLY_BACK
    if (wind)
        wind->ShowResult(n);
    
    #else
    if (!n)
        std::cout <<"Sorry Bro, Not Solution Found" << std::endl;
    else 
        std::cout <<std::endl<< "Great, a solution has been found "<<std::endl;
    #endif
    return n;

} 
}
#endif
