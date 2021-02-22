#include <iostream> 
#include <list>
#include "Node.hpp"
#include "Problem.hpp"
#include "Algorithm.hpp"
#ifndef TREE_HPP
#define TREE_HPP
#ifndef ONLY_BACK
class MainWindow;
class WorkerThread;
#endif
namespace AI
{
template <typename T>
class Tree  
{ 
  public: 
  #ifdef ONLY_BACK
    std::shared_ptr<Node<T>>  Tree_Search(std::shared_ptr<Problem<T>> &p, std::unique_ptr<Algorithm<T>> &al); 
  #else
    std::shared_ptr<Node<T>>  Tree_Search(std::shared_ptr<Problem<T>> &p, std::unique_ptr<Algorithm<T>> &al, WorkerThread *wind); 
  #endif
private:
    //Track a list of visited states
    bool TrackStates;
    
    //Visited states
    std::shared_ptr<Node<T>> VisitedStates;

}; 
}
#include "../Private/Tree.tpp"

#endif