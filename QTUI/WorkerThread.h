#include "../BackEnd/Public/Initialize.hpp"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QObject>
#include <QEventLoop>
#include <atomic>    
#include <ctime>
#include <chrono>
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
class MainWindow;
//Q_DECLARE_METATYPE(ProblemType)
using namespace AI;

class WorkerThread : public QObject
{
    Q_OBJECT

public slots:
    void StartBackend(    ProblemType pt, AlgorithmType at, int size,bool useGraphSearch );
signals:
    void HasInit(bool hasInit);
    void resultReady(const QString &s);
public:
    void getState(NodeData data, int depth, int numNodes, std::vector<int> childNum, bool isInitial=true);
    void ShowResult(std::shared_ptr<Node<NodeData>>  data);
    WorkerThread(MainWindow *win) {_win = win;}
    void LoopPauseGame();
    std::atomic<bool> _reset = false;
    std::atomic<bool> _useOneStep = true;
    std::atomic<bool> _oneStepPresed =false;
    QMutex mutex;
private:
    MainWindow *_win;
    Initialize<NodeData> *init=nullptr;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

};

#endif // MAINWINDOW_H
