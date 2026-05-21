#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <QVector>
#include <limits>
class BFS
{
private:
    QVector<int> m_level;
    QVector<int> m_parent;
public:
    BFS();
    void run(const graph&g, int start);
    const QVector<int>& level() const;
    const QVector<int>& parent() const;
};

#endif // BFS_H
