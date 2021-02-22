#include "../Algorithm.hpp"
#include "../NodeData.hpp"
#ifndef ASTAR_HPP
#define ASTAR_HPP
namespace AI
{
class AStarSearchAlgorithm : public Algorithm<NodeData>
{
public:
    AStarSearchAlgorithm(){}
    std::shared_ptr<Node<NodeData>> GetSuccessorChilds(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n);

    std::shared_ptr<Node<NodeData>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n);
    int CalculateSeparation(int a, int b, int size);
    //std::shared_ptr<Node<NodeData>> GetFirstNodeFromLvl(std::shared_ptr<Node<NodeData>> n);
    void CalculateH(std::shared_ptr<Node<NodeData>> n,std::shared_ptr<Problem<NodeData>> p);
    /**
    * Search for nodes not visited
    **/
    void  GetNodeToUse(std::shared_ptr<Node<NodeData>> n, int f, bool increaseF);
    
    std::shared_ptr<Node<NodeData>> GetParent(std::shared_ptr<Node<NodeData>> n);
private:
    std::shared_ptr<Node<NodeData>> lower_f_node=nullptr;
  
};
}
#endif