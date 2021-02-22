#include "../BackEnd/Public/Initialize.hpp"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QWaitCondition>
#include <QMutex>
#include "WorkerThread.h"
#include <QThread>
#include <QCheckBox>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


using namespace AI;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class WorkerThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void StartBackendOneStep();
    void StartBackendEntirely();
    void StartBackend();


    void handleReset();
    void handleShowMetrics();
signals:
    void StartBackendSignal(    ProblemType pt, AlgorithmType at, int size, bool useGraphSearch );

public:
    QLabel *initial_state_label;
    QLabel *final_state_label;
    QLabel *metrics_label;
public slots:
    void HasInit(bool hasInit) {_init = hasInit;};

    void handleResults(const QString &);
private:
    bool _init = false;
    QLabel *algorithm_label;
    QLabel *problem_label;
    QLabel *size_label;

    Ui::MainWindow *ui;
    QPushButton *_reset;
    QPushButton *_do_one_step;
    QPushButton *_pause_solving;
    QPushButton *_solveEntirely;
    QPushButton *_showMetric;
    QListWidget *AlgorithmChoice;
    QListWidget *ProblemChoice;
    QListWidget *Size;

    WorkerThread *workerThread;
    QCheckBox *_checkbox;
};


#endif // MAINWINDOW_H
