#include "../Public/Node.hpp"
#include "../Public/NodeData.hpp"
#include "../Public/Algorithm.hpp"
#ifndef UTILITTIES
#define UTILITTIES
namespace AI{
void StringInfo(std::shared_ptr<Node<NodeData>> node)
{
    std::vector<Variant> data = node->getData()._data;
    std::cout <<"size: "<<node->getData()._size <<std::endl;
    std::string str = "";

    for (auto it = data.begin(); it != data.end(); it++) {
        std::cout << (*it)._asInt;
        std::cout << ",";
    }
    std::cout << std::endl;
}
}
#endif
