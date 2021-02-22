#include "../Algorithm.hpp"
#include "../NodeData.hpp"
#ifndef BREATHFIRSTSEARCHAL_HPP
#define BREATHFIRSTSEARCHAL_HPP
namespace AI
{
class BreadthFirstSearchAlgorithm : public Algorithm<NodeData>
{
public:
    BreadthFirstSearchAlgorithm(){}
    std::shared_ptr<Node<NodeData>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n);
    /**
    * Search for nodes not visited
    **/
    std::shared_ptr<Node<NodeData>> GetFirstNodeFromLvl(std::shared_ptr<Node<NodeData>> n);
    /**
    * Search for nodes not used
    **/
   std::shared_ptr<Node<NodeData>> GetFirstNodeFromNextLvl(std::shared_ptr<Node<NodeData>> n);

    std::shared_ptr<Node<NodeData>> GetParent(std::shared_ptr<Node<NodeData>> n);
private:
};
}
#endif