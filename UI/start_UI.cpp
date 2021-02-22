
#include "../BackEnd/Public/Node.hpp"
#include "../BackEnd/Public/NodeData.hpp"
#include "../BackEnd/Public/Algorithm.hpp"
#include "../BackEnd\Public\Problems\Puzzle\PuzzleGenerator.hpp"
#include "../BackEnd/Public/BreadthFirstSearch/BreadthFirstSearchAlgorithm.hpp"
#include <QtWidgets/QApplication>
#include <QPushButton>

int startUI(int argc, char **argv) 
{
    QApplication app (argc, argv);
    QPushButton button;
    button.setText("My text");
    button.setToolTip("A tooltip");
    button.show();
    return app.exec();
}