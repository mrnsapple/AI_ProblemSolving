
#include "Node.hpp"
#ifndef PROBLEM_HPP
#define PROBLEM_HPP
namespace AI
{
enum ProblemType;
enum AlgorithmType;

template <typename T>
class Problem
{
public:
    Problem(ProblemType pt, AlgorithmType algorithmtype){ 
        std::cout << "IN PROBLEM CONSTRUCTOR" << std::endl;
        _problemType = pt;
        _algorithmtype = algorithmtype; }
    ProblemType GetType() { return _problemType; }
    AlgorithmType GetAlgorithmType() { return _algorithmtype; }

    std::shared_ptr<Node<T>> GetInitialState() { return _initial_state; };
    void SetInitialState(std::shared_ptr<Node<T>> n) { _initial_state = n;}
    std::shared_ptr<Node<T>> GetDesiredState(){ return _desired_state;}
    void SetDesiredState(std::shared_ptr<Node<T>> n){ _desired_state = n;}
    bool compare(std::shared_ptr<Node<T>> node ,std::shared_ptr<Node<T>> other=nullptr);
    void setUseGraphSearch(bool useGraphSearch) {_useGraphSearch = useGraphSearch;}
    bool getUseGraphSearch() {return _useGraphSearch;}
    std::list<std::shared_ptr<Node<T>>> CheckNodes( std::list<std::shared_ptr<Node<T>>> nodes);
    bool CheckNode(std::shared_ptr<Node<T>> nodedata);
private:
    ProblemType _problemType;
    AlgorithmType _algorithmtype;

    std::shared_ptr<Node<T>> _initial_state; 
    std::shared_ptr<Node<T>> _desired_state; 
    bool _useGraphSearch;
     std::list<std::shared_ptr<Node<T>>> _visited_states;
};
}
#include "../Private/Problem.tpp"

#endif