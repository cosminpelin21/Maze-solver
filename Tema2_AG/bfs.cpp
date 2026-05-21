#include "bfs.h"
#include <QQueue>
BFS::BFS() {}

void BFS::run(const graph &g, int start)
{
    int n = g.nodeCount();
    m_level.assign(n, 0);
    m_parent.assign(n, -1);

    if (start < 0 || start >= n)
        return;
    QQueue<int> q;
    m_level[start] = 1;
    m_parent[start] = -1;
    q.enqueue(start);

    while (!q.isEmpty()) {
        int x = q.dequeue();
        const QVector<int> &neighbors = g.adj(x);
        for (int y : neighbors) {
            if (m_level[y] == 0) {
                m_parent[y] = x;
                m_level[y] = m_level[x] + 1;
                q.enqueue(y);
            }
        }
    }
}

const QVector<int> &BFS::level() const
{
    return m_level;
}

const QVector<int> &BFS::parent() const
{
    return m_parent;
}
