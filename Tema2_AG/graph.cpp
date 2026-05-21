#include "graph.h"

graph::graph(): m_rows(0), m_cols(0), m_entry(-1){}

void graph::buildMaze(const labirint &maze)
{
    m_adjList.clear();
    m_id2cell.clear();
    m_mapId.clear();
    m_exits.clear();
    m_entry = -1;
    m_rows = maze.rows();
    m_cols = maze.collumns();
    if (m_rows == 0 || m_cols == 0)
        return;
    m_mapId.assign(m_rows, QVector<int>(m_cols, -1));
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            char ch = maze.cell(i, j);
            if (ch != '0') {
                int id = m_id2cell.size();
                m_id2cell.append({i,j});
                m_mapId[i][j] = id;
                m_adjList.append(QVector<int>());
                if (ch == '3')
                    m_entry = id;
                if (ch == '2')
                    m_exits.append(id);
            }
        }
    }
    int directionRow[4] = {-1,1,0,0};
    int directionColl[4] = {0,0,-1,1};
    for (int id = 0; id < m_id2cell.size(); id++) {
        int row = m_id2cell[id].first;
        int col = m_id2cell[id].second;
        for (int k = 0; k < 4; k++) {
            int nr = row + directionRow[k];
            int nc = col + directionColl[k];
            if (nr < 0 || nr >= m_rows || nc < 0 || nc >= m_cols)
                continue;
            int neighbourID = m_mapId[nr][nc];
            if (neighbourID != -1) {
                m_adjList[id].append(neighbourID);
            }
        }
    }
}

int graph::nodeCount() const
{
    return m_adjList.size();
}

const QVector<int> &graph::adj(int u) const
{
    return m_adjList[u];
}

int graph::cellToId(int row, int col) const
{
    if (row < 0 || row >= m_mapId.size())
        return -1;
    if (m_mapId[row].isEmpty())
        return -1;
    if (col < 0 || col >= m_mapId[row].size())
        return -1;
    return m_mapId[row][col];
}

QPair<int, int> graph::idToCell(int id) const
{
     return m_id2cell[id];
}

QVector<int> graph::exitNodes() const
{
    return m_exits;
}

int graph::entryNode() const
{
    return m_entry;
}
