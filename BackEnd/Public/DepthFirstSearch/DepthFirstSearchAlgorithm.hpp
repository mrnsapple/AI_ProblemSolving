#include "../Algorithm.hpp"
#include "../NodeData.hpp"
#ifndef DEPTH_FIRSTSEARCH_HPP
#define DEPTH_FIRSTSEARCH_HPP
namespace AI
{
class DepthFirstSearchAlgorithm : public Algorithm<NodeData>
{
public:
    DepthFirstSearchAlgorithm(){}
    std::shared_ptr<Node<NodeData>> GetSuccessor(std::shared_ptr<Problem<NodeData>> p, std::shared_ptr<Node<NodeData>> n);
  
    /**
    * Search for nodes not used
    **/
   std::shared_ptr<Node<NodeData>> GetNextNode(std::shared_ptr<Node<NodeData>> n);
private:
};
}
#endif