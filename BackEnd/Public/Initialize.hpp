#include "Tree.hpp"
#include "Node.hpp"
#include "NodeData.hpp"
#include "Algorithm.hpp"
#include "Problems\Puzzle\PuzzleGenerator.hpp"
#include "BreadthFirstSearch\BreadthFirstSearchQueenLogic.hpp"
#include "AStar/AStarSearchAlgorithm.hpp"
#include "BreadthFirstSearch\BreadthFirstSearchPuzzleLogic.hpp"
#include "BreadthFirstSearch/BreadthFirstSearchAlgorithm.hpp"
#include "BackEnd\Public\DepthFirstSearch\DepthFirstSearchAlgorithm.hpp"
#include "BackEnd\Public\SimulatedAnnealing\SimulatedAnnealingAlgorithm.hpp"
#ifndef INITIALIZE_HPP
#define INITIALIZE_HPP

#ifndef ONLY_BACK
class MainWindow;
class WorkerThread;
#endif
namespace AI
{

enum ProblemType
{
    Puzzle,
    Queen
};
enum AlgorithmType
{
    BreadthFirstSearch,
    AStar,
    GreedySearch,
    SimulatedAnnealing,
    HillClimbing,
    DepthFirstSearch
};
template <typename T>
class Initialize
{
public:
#ifdef ONLY_BACK
    Initialize(ProblemType pt, AlgorithmType at, int map_size,  bool useGraphSearch=false);
#else    
    Initialize(ProblemType pt, AlgorithmType at, int map_size, WorkerThread * wind, bool useGraphSearch=false);
#endif
    void MakeTree();
    std::unique_ptr<Algorithm<T>> GetAlgorithm();
    std::shared_ptr<Problem<T>> GetProblem();
    void PrintInfo(std::shared_ptr<Node<NodeData>> node);
private:
    ProblemType _problemtype;
    AlgorithmType _algorithmtype;
    int _map_size;
    bool _useGraphSearch;
#ifndef ONLY_BACK
    WorkerThread * _wind = nullptr;
#endif
};
}
#include "../Private/Initialize.tpp"

#endif