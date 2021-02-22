
#include "../../Node.hpp"

#include "../../NodeData.hpp"
#ifndef PUZZLEGENERATOR_HPP
#define PUZZLEGENERATOR_HPP
namespace AI
{
class PuzzleGenerator
{   
public:
    static std::shared_ptr<Node<NodeData>> GetEmptyState(int size);
    static std::shared_ptr<Node<NodeData>> AddElement(std::shared_ptr<Node<NodeData>> node);
    static std::shared_ptr<Node<NodeData>> GetRandomInitialState(int size);
    static std::shared_ptr<Node<NodeData>>  GetDesiredState(int size);
private:
};
}
#endif