#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace AI;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<ProblemType>("ProblemType");
    qRegisterMetaType<AlgorithmType>("AlgorithmType");
    //qRegisterMetaType<Initialize<NodeData>>("Initialize<NodeData>");

    ui->setupUi(this);
    _reset = new QPushButton("Reset", this);
    _showMetric = new QPushButton("Show Metrics", this);
    _do_one_step = new QPushButton("Do one step", this);
    _pause_solving = new QPushButton("Pause Solving", this);
    _solveEntirely = new QPushButton("Solve Entirely", this);
    
    _checkbox  = new QCheckBox("Use Graph Search", this);
    _checkbox->setGeometry(QRect(630,320,200,200));  

    _reset->setGeometry(QRect( QPoint(10, 0), QSize(200, 50) ));
    _showMetric->setGeometry(QRect( QPoint(10, 50), QSize(200, 50) ));
    _do_one_step->setGeometry(QRect( QPoint(10, 150), QSize(200, 50) ));
    _pause_solving->setGeometry(QRect( QPoint(10, 100), QSize(200, 50) ));
    _solveEntirely->setGeometry(QRect( QPoint(10, 200), QSize(200, 50) ));

    metrics_label = new QLabel(this);
    metrics_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    metrics_label->setText("Metrics\nNumber Nodes:\nTime taken:\nAverage Branching:\nMax Depth:\n");
    metrics_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    metrics_label->setGeometry(QRect(10,260,250,250));  
    size_label = new QLabel(this);
    size_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    size_label->setText("Select Size:");
    size_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    size_label->setGeometry(QRect(430,430,100,30));    
    algorithm_label = new QLabel(this);
    algorithm_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    algorithm_label->setText("Select Algorithm:");
    algorithm_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    algorithm_label->setGeometry(QRect(220,20,100,30));  
    problem_label = new QLabel(this);
    problem_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    problem_label->setText("Select Problem:");
    problem_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    problem_label->setGeometry(QRect(530,20,100,30));  
    final_state_label = new QLabel(this);
    final_state_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    final_state_label->setText("THERE IS NOT A FINAL STATE");
    final_state_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    final_state_label->setGeometry(QRect(530,120,200,200));  
    initial_state_label = new QLabel(this);
    initial_state_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    initial_state_label->setText("THERE IS NOT AN INITIAL STATE");
    initial_state_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    initial_state_label->setGeometry(QRect(330,120,200,200));  
    //Connect button signal to appropriate slot
    connect(_reset, SIGNAL (clicked()),this, SLOT (handleReset()));
    connect(_showMetric, SIGNAL (clicked()),this, SLOT (handleShowMetrics()));
    connect( _do_one_step, SIGNAL (clicked()),this, SLOT (StartBackendOneStep()));
    connect(  _solveEntirely, SIGNAL (clicked()),this, SLOT (StartBackendEntirely()));
    connect( _pause_solving, SIGNAL (clicked()),this, SLOT (StartBackendOneStep()));

    AlgorithmChoice= new QListWidget(this);
    AlgorithmChoice->setGeometry(QRect(220,60,260,50)); 
    new QListWidgetItem(tr("Breadth First Search(uninformed)"), AlgorithmChoice);
    new QListWidgetItem(tr("Depth First Search(uninformed)"), AlgorithmChoice);
    new QListWidgetItem(tr("A*(informed)"), AlgorithmChoice);
    new QListWidgetItem(tr("Greedy Search(informed)"), AlgorithmChoice);
    new QListWidgetItem(tr("Simulated Annealing(local)"), AlgorithmChoice);
    new QListWidgetItem(tr("Hill Climbing(local)"), AlgorithmChoice);

    ProblemChoice= new QListWidget(this);
    ProblemChoice->setGeometry(QRect(530,60,260,50)); 
    new QListWidgetItem(tr("Puzzle"), ProblemChoice);
    new QListWidgetItem(tr(" Queens"), ProblemChoice);
    Size =  new QListWidget(this);
    Size->setGeometry(QRect(430,460,260,100)); 
    for (int i = 2; i < 50; i++)
        new QListWidgetItem(tr(std::to_string(i).c_str()), Size);
    new QListWidgetItem(tr("1000000"), Size);

    workerThread = new WorkerThread(this);
    connect(this, &MainWindow::StartBackendSignal, workerThread, &WorkerThread::StartBackend, Qt::AutoConnection);
    connect( workerThread, &WorkerThread::HasInit, this, &MainWindow::HasInit, Qt::AutoConnection);
    // //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);    
}

void MainWindow::StartBackendOneStep()
{
        workerThread->_reset = false;

    workerThread->_useOneStep = true;
    workerThread->_oneStepPresed =true;
   StartBackend();
}

void MainWindow::StartBackendEntirely()
{
        workerThread->_reset = false;

    workerThread->_useOneStep = false;
    workerThread->_oneStepPresed =true;
    StartBackend();

}


void MainWindow::handleResults(const QString &str)
{
    std::cout << "IN HANDLE RESULTS" << std::endl;
} 

void MainWindow::StartBackend()
{
    ProblemType pt;
    AlgorithmType at;
    int size = 0;
    if (! ProblemChoice->currentItem() || ! AlgorithmChoice->currentItem()) {
        std::cout << "Algorithm or Problem not selected"<< std::endl;
        return;
    }
    std::string problemChoiceString = ProblemChoice->currentItem()->text().toStdString();
    std::string AlgorithmChoiceString = AlgorithmChoice->currentItem()->text().toStdString();
    std::string SizeChoiceString = Size->currentItem()->text().toStdString();

    std::cout << "Problem Selected:" << problemChoiceString << std::endl;
    std::cout << "AlgorithmChoice Selected:" << AlgorithmChoiceString << std::endl;
    if (! _init) {
        if (problemChoiceString == "Puzzle")
             pt = ProblemType::Puzzle;
        else
             pt = ProblemType::Queen;
        if (AlgorithmChoiceString == "Breadth First Search(uninformed)")
            at = AlgorithmType::BreadthFirstSearch;
        else if (AlgorithmChoiceString == "A*(informed)")
            at = AlgorithmType::AStar;
        else if (AlgorithmChoiceString == "Depth First Search(uninformed)")
            at = AlgorithmType::DepthFirstSearch;
        else if (AlgorithmChoiceString == "Greedy Search(informed)")
            at = AlgorithmType::GreedySearch;
        else if (AlgorithmChoiceString == "Simulated Annealing(local)")
            at = AlgorithmType::SimulatedAnnealing;
        else if (AlgorithmChoiceString == "Hill Climbing(local)")
            at = AlgorithmType::HillClimbing;
        try {
            size = atoi(SizeChoiceString.c_str())*atoi(SizeChoiceString.c_str());
        } catch( ... ){
            size = 3;
        }
        QThread *thread = new QThread;
        workerThread->moveToThread(thread);
        thread->start();
        emit StartBackendSignal(pt, at, size, _checkbox->isChecked());
    }
    else {
      // std::cout << "Already initialize" << std::endl;

    }
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleShowMetrics()
{
    metrics_label->setVisible(!metrics_label->isVisible());
}

void MainWindow::handleReset()
{

    // std::cout << "HANDLE RESET" << std::endl;
    workerThread->_reset = true;
    workerThread->_oneStepPresed =true;
    _init = false;

    //final_state_label->setText("RESET DONE, Current State:")
    
    initial_state_label->setText("RESET DONE, Current State:");
    //change the text
    //_reset->setText("Example");
    //resize button
    //m_pButton->resize(100,100);
}
