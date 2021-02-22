#include "../Algorithm.hpp"
#include "../NodeData.hpp"

#ifndef BreadthFirstSearchQueenLogic_HPP
#define BreadthFirstSearchQueenLogic_HPP
namespace AI
{
class BreadthFirstSearchQueenLogic : public AlgorithmLogic<NodeData>
{
public:
    std::list<std::shared_ptr<Node<NodeData>>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)  override;
    std::vector<int> GetPositionsToChange(NodeData nodedata);
    bool CheckLocation(int pos, NodeData nodedata);
    int GetYDistance(int pos, int size, int amount);
    int GetXDistance(int pos, int size, int amount);

    std::list<std::shared_ptr<Node<NodeData>>> MakeNodes(NodeData nodedata,  std::vector<int> Positions,std::shared_ptr<Node<NodeData>> parent);
};
}
#endif