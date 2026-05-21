#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_scene(new QGraphicsScene(this))
    , m_cellSize(50)
{
    m_ui->setupUi(this);
    m_ui->graphicsView->setScene(m_scene);

    connect(m_ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    connect(m_ui->drawMazeButton, &QPushButton::clicked, this, &MainWindow::on_drawMazeButton_clicked);
    connect(m_ui->buildGraphButton, &QPushButton::clicked, this, &MainWindow::on_buildGraphButton_clicked);
    connect(m_ui->bfsButton, &QPushButton::clicked, this, &MainWindow::on_bfsButton_clicked);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("choose maze"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) return;
    m_maze.readFile(fileName);
    if (!m_maze.valid()) {
        QMessageBox::warning(this, tr("error"), tr("the maze could not be read"));
        return;
    }
    m_scene->clear();
}

void MainWindow::on_buildGraphButton_clicked()
{
    if (!m_maze.valid()) {
        QMessageBox::information(this, tr("info"), tr("you didn't choose any maze"));
        return;
    }
    m_graph.buildMaze(m_maze);
    m_scene->clear();
    drawMaze();
    drawGraph();
}

void MainWindow::on_drawMazeButton_clicked()
{
    if (!m_maze.valid()) {
        QMessageBox::information(this, tr("info"), tr("first choose the maze"));
        return;
    }
    m_scene->clear();
    drawMaze();
}

void MainWindow::drawMaze()
{
    const auto &g = m_maze.grid();
    int r = m_maze.rows();
    int c = m_maze.collumns();
    m_scene->setSceneRect(0,0,c*m_cellSize, r*m_cellSize);

    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            QRectF rect(j*m_cellSize, i*m_cellSize, m_cellSize, m_cellSize);
            QGraphicsRectItem *item = m_scene->addRect(rect);
            char ch = g[i][j].toLatin1();
            if (ch == '0') {
                item->setBrush(Qt::black);
            } else if (ch == '1')
            {
                item->setBrush(Qt::white);
            } else if (ch == '3')
            {
                item->setBrush(Qt::blue);
            } else if (ch == '2')
            {
                item->setBrush(Qt::red);
            } else {
                item->setBrush(Qt::white);
            }
            item->setPen(QPen(Qt::gray));
        }
    }
}

void MainWindow::drawGraph()
{
    if (m_graph.nodeCount() == 0)
        return;
    for (int u = 0; u < m_graph.nodeCount(); u++) {
        auto rowCol = m_graph.idToCell(u);
        QPointF center(rowCol.second*m_cellSize + m_cellSize/2.0, rowCol.first*m_cellSize + m_cellSize/2.0);
        for (int v : m_graph.adj(u)) {
            if (v <= u)
                continue;
            auto rowCol2 = m_graph.idToCell(v);
            QPointF center2(rowCol2.second*m_cellSize + m_cellSize/2.0, rowCol2.first*m_cellSize + m_cellSize/2.0);
            QGraphicsLineItem *line = m_scene->addLine(QLineF(center, center2), QPen(Qt::black));
            line->setZValue(0.5);
        }
        QGraphicsEllipseItem *node = m_scene->addEllipse(center.x()-8, center.y()-8, 16, 16, QPen(Qt::black), QBrush(Qt::cyan));
        node->setZValue(1.0);
    }
}

void MainWindow::on_bfsButton_clicked()
{
    if (!m_maze.valid()) {
        QMessageBox::information(this, tr("info"), tr("you didn't choose any maze"));
        return;
    }
    m_graph.buildMaze(m_maze);
    int start = m_graph.entryNode();
    if (start < 0) {
        QMessageBox::warning(this, tr("error"), tr("the maze does not contain any starting points"));
        return;
    }
    BFS bfs;
    bfs.run(m_graph, start);
    m_bfsParent = bfs.parent();
    m_bfsLevel = bfs.level();
    m_scene->clear();
    drawMaze();
    drawPathsToExits();
}

void MainWindow::drawPathsToExits()
{
    if (m_bfsParent.isEmpty() || m_bfsLevel.isEmpty())
        return;
    QVector<int> exits = m_graph.exitNodes();
    QBrush pathBrush(Qt::green);
    QPen noPen(Qt::NoPen);
    for (int exit : exits) {
        if (exit < 0 || exit >= m_graph.nodeCount())
            continue;
        if (m_bfsLevel[exit] == 0)
            continue;
        QVector<int> path;
        int current = exit;
        while (current != -1) {
            path.append(current);
            current = m_bfsParent[current];
        }
        for (int id : path) {
            QPair<int,int> rc = m_graph.idToCell(id);
            int row = rc.first;
            int col = rc.second;
            QChar qc = m_maze.grid()[row][col];
            char ch = qc.toLatin1();
            if (ch != '1')
                continue;
            m_scene->addRect(col * m_cellSize, row * m_cellSize,
                        m_cellSize, m_cellSize, noPen, pathBrush)->setZValue(2);
        }
    }
}
