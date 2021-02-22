#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "WorkerThread.h"
using namespace AI;

void WorkerThread::StartBackend(    ProblemType pt, AlgorithmType at, int size,bool useGraphSearch )
{
     begin = std::chrono::steady_clock::now();
    if (size == 1000000)
        init =  new Initialize<NodeData>(pt,at,size, nullptr,  useGraphSearch);    
    else
        init =  new Initialize<NodeData>(pt,at,size, this,  useGraphSearch);    
    emit HasInit(true);
    init->MakeTree();
}

void WorkerThread::LoopPauseGame()
{
    std::cout <<std::endl<< "BEFORE LOOP PAUSE:"<<std::endl;
    mutex.lock();
    if (_useOneStep)
        while (!_oneStepPresed) {}
    mutex.unlock();
    std::cout <<std::endl<< "AFTER LOOP PAUSE:"<<std::endl;
    _oneStepPresed =false;
}

void WorkerThread::ShowResult(std::shared_ptr<Node<NodeData>> data)
{
    std::string state = "";
    int averageBranching = 0;
    int i = 0;
    if (!data)
        _win->initial_state_label->setText("No Solution Found");
    else {
        NodeData datadata= data->getData();
        std::vector<Variant> datav = datadata._data;

        for (auto it = datav.begin(); it != datav.end(); it++) {
            if (i % (int)sqrt( (int)datadata._size) == 0)
                state += "\n";
            i++;    
            state += std::to_string((*it)._asInt) + ","; 
        }
        if (_win && _win->initial_state_label) {
            state = "Solution Found:\n" + state;
            _win->initial_state_label->setText(QString::fromUtf8(state.c_str()));
        }
    }
}


void WorkerThread::getState(NodeData data, int depth, int numNodes,  std::vector<int> childNum, bool isInitial)
{
    std::vector<Variant> datav = data._data;
    std::string state = "";
    std::string metrics = "";
    int averageBranching = 0;
    int i = 0;
    for (auto it = datav.begin(); it != datav.end(); it++) {
        if (i % (int)sqrt( (int)data._size) == 0) {
            std::cout << std::endl;
            state += "\n";
        }
        i++;    
        state += std::to_string((*it)._asInt) + ",";
        std::cout << (*it)._asInt;
        std::cout << ",";
        
    }
    if (isInitial && _win && _win->initial_state_label) {
        state = "Current State:\n" + state;
        _win->initial_state_label->setText(QString::fromUtf8(state.c_str()));
    }
    else if (!isInitial && _win && _win->initial_state_label) {
        state = "Final State:\n" + state;
    
        _win->final_state_label->setText(QString::fromUtf8(state.c_str()));
    }
    for (int i = 0; i < childNum.size();i++)
        averageBranching+=childNum[i];
    averageBranching = int(float(averageBranching)/float(childNum.size()));
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    metrics.append("Metrics\nNumber Nodes:");
    metrics.append(std::to_string(numNodes));
    metrics.append("\nTime taken: ");
    metrics.append(std::to_string( std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()));
    metrics.append(" microseconds\nAverage Branching: ");
    metrics.append(std::to_string(averageBranching));
    metrics.append("\nMax Depth: ") ;
    metrics.append(std::to_string(depth));
    _win->metrics_label->setText(QString::fromUtf8(metrics.c_str()));
}
