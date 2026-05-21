#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "labirint.h"
#include "graph.h"
#include "bfs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_buildGraphButton_clicked();
    void on_drawMazeButton_clicked();
    void on_bfsButton_clicked();
private:
    Ui::MainWindow *m_ui;
    QGraphicsScene *m_scene;
    labirint m_maze;
    graph m_graph;
    int m_cellSize;
    QVector<int> m_bfsParent;
    QVector<int> m_bfsLevel;

    void drawMaze();
    void drawGraph();
    void drawPathsToExits();
};
#endif // MAINWINDOW_H
