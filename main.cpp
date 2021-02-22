#include "BackEnd/Public/Initialize.hpp"
using namespace AI;

void GetChoice()
{
    int problem_choice;
    int map_size;
    int algorithm;
    std::cout << "Select Problem" << std::endl<< "1 for Puzzle:"<< std::endl<<"2 for queen:" << std::endl;
    std::cin >> problem_choice;
    std::cout << "Select map size:" << std::endl;
    std::cin >> map_size;
    std::cout << problem_choice << std::endl;
    std::cout << "Select algorithm choice:" << std::endl << "1 for BreadthFirstSearch:";
    std::cin >> algorithm;

}

// Driver code 
int main(int argc, char **argv) 
{ 

    //GetChoice();
    Initialize<NodeData> init(ProblemType::Queen,AlgorithmType::HillClimbing,1000000, false);

    //Initialize<NodeData> init(ProblemType::Puzzle,AlgorithmType::HillClimbing,9, false);
    //Initialize<NodeData> init(ProblemType::Queen,AlgorithmType::BreadthFirstSearch,16, false);
    init.MakeTree();
    return 0; 
} 
  
