#include "../Algorithm.hpp"
#include "../NodeData.hpp"

#ifndef BreadthFirstSearchPuzzleLogic_HPP
#define BreadthFirstSearchPuzzleLogic_HPP
namespace AI
{
class BreadthFirstSearchPuzzleLogic : public AlgorithmLogic<NodeData>
{
public:
    std::list<std::shared_ptr<Node<NodeData>>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n)  override;
    std::vector<int> GetPositionsToChange(int size, int currentpos);
    int GetEmptyCellPosition(std::shared_ptr<Node<NodeData>> n);
    std::list<std::shared_ptr<Node<NodeData>>> MakeNodes(NodeData nodedata,  std::vector<int> Positions, int currentPos,std::shared_ptr<Node<NodeData>> parent);
};
}
#endif