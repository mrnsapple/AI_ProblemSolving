#include "../Public/NodeData.hpp"
#ifndef INITIALIZE_TPP
#define INITIALIZE_TPP
namespace AI
{
    template <typename T>
    void Initialize<T>::PrintInfo(std::shared_ptr<Node<NodeData>> node)
    {
        T a;
        std::vector<Variant> data = node->getData()._data;
        std::cout <<"size: "<<node->getData()._size <<std::endl;
        std::string str = "";
        int i = 1;
            for (auto it = data.begin(); it != data.end(); it++) {
                std::cout << (*it)._asInt;
                
                std::cout << ",";
                if (i % (int)sqrt( (int)node->getData()._size) == 0)
                    std::cout << std::endl;
                i++;
            }
        std::cout << std::endl;
    }

    #ifdef ONLY_BACK
        template <typename T>
        Initialize<T>::Initialize(ProblemType pt, AlgorithmType at, int map_size, bool useGraphSearch)
    #else    
        template <typename T>
        Initialize<T>::Initialize(ProblemType pt, AlgorithmType at, int map_size, WorkerThread * wind, bool useGraphSearch)
    #endif
    {
        _problemtype = pt;
        _algorithmtype = at;
        _map_size = map_size;
        _useGraphSearch = useGraphSearch;
        #ifndef ONLY_BACK
            _wind = wind;
        #endif
    }

    template <typename T>
    void Initialize<T>::MakeTree()
    {
        Tree<T> tree;
        std::shared_ptr<Problem<T>> p = GetProblem();
        
        std::unique_ptr<Algorithm<T>> al = GetAlgorithm();
        #ifdef ONLY_BACK
            tree.Tree_Search(p, al);
        #else
            tree.Tree_Search(p, al, _wind);
        
        #endif
    }

    template <typename T>
    std::unique_ptr<Algorithm<T>> Initialize<T>::GetAlgorithm()
    {
        std::unique_ptr<Algorithm<T>> al = nullptr;
        AlgorithmLogic<T> *logic = nullptr;
        if (_problemtype == Puzzle) 
            logic =new BreadthFirstSearchPuzzleLogic();
        else 
            logic =new BreadthFirstSearchQueenLogic();   
        if (_algorithmtype == BreadthFirstSearch)
            al = std::make_unique<BreadthFirstSearchAlgorithm>();
        else if (_algorithmtype == DepthFirstSearch)
            al = std::make_unique<DepthFirstSearchAlgorithm>();
        else if (_algorithmtype == AStar)
            al = std::make_unique<AStarSearchAlgorithm>();
        else if (_algorithmtype == GreedySearch)
            al = std::make_unique<AStarSearchAlgorithm>();
        else if (_algorithmtype == SimulatedAnnealing || _algorithmtype == HillClimbing)
            al = std::make_unique<SimulatedAnnealingAlgorithm>();
        if (al)
            al->setAlgorithmLogic(logic);
        return al;
    }
    
    template <typename T>
    std::shared_ptr<Problem<T>> Initialize<T>::GetProblem()
    {
        std::shared_ptr<Node<T>> desiredNode; 
        std::shared_ptr<Node<T>> initialNode;
        std::shared_ptr<Problem<T>> p=std::make_shared<Problem<T>>(_problemtype, _algorithmtype);
        initialNode = PuzzleGenerator::GetRandomInitialState(_map_size);
        desiredNode = PuzzleGenerator::GetDesiredState(_map_size);
        if (_problemtype == Queen)
            initialNode = PuzzleGenerator::GetEmptyState(_map_size);
    
        if (_algorithmtype == AStar || _algorithmtype == GreedySearch || _algorithmtype == SimulatedAnnealing || _algorithmtype == HillClimbing) {
            for (int i = 0; i < 2; i++) {
                initialNode = PuzzleGenerator::AddElement(initialNode);
                desiredNode = PuzzleGenerator::AddElement(desiredNode);
            }
        }
        std::cout <<"INITIAL:" << std::endl;
        PrintInfo(initialNode);
        std::cout <<"DDESIRED:" << std::endl;
        PrintInfo(desiredNode);
        p->SetInitialState(initialNode);
        p->SetDesiredState(desiredNode);
        p->setUseGraphSearch(_useGraphSearch);
        return p;
    
    }




}
#endif