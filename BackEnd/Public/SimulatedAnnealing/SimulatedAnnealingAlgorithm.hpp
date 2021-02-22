#include "../Algorithm.hpp"
#include "../NodeData.hpp"
#ifndef SimulatedAnnealingAlgorithm_HPP
#define SimulatedAnnealingAlgorithm_HPP
namespace AI
{
class SimulatedAnnealingAlgorithm : public Algorithm<NodeData>
{
public:
    SimulatedAnnealingAlgorithm(){}

    std::shared_ptr<Node<NodeData>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n);
    //std::shared_ptr<Node<NodeData>> GetFirstNodeFromLvl(std::shared_ptr<Node<NodeData>> n);
    void CalculateH(std::shared_ptr<Node<NodeData>> n,std::shared_ptr<Problem<NodeData>> p);
    /**
    * Search for nodes not visited
    **/
    std::shared_ptr<Node<NodeData>>   GetNodeToUse(std::shared_ptr<Node<NodeData>> n, int f, bool useRandom);
    
private:
    int h = 0;
    int temp = 4000;
    int f = 0;
};
}
#endif