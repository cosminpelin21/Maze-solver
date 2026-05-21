#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPair>
#include "labirint.h"

class graph
{
private:
    QVector<QVector<int>> m_adjList;
    QVector<QPair<int,int>> m_id2cell;
    QVector<QVector<int>> m_mapId;
    int m_rows, m_cols;
    int m_entry;
    QVector<int> m_exits;
public:
    graph();
    void buildMaze(const labirint &maze);
    int nodeCount() const;
    const QVector<int>& adj(int u) const;
    int cellToId(int row, int col) const;
    QPair<int,int> idToCell(int id) const;
    QVector<int> exitNodes() const;
    int entryNode() const;
};

#endif // GRAPH_H
