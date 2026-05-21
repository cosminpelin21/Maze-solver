#include "labirint.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

labirint::labirint() {}

void labirint::readFile(const QString &file)
{
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "file cannot open";
        m_grid.clear();
        return;
    }
    m_grid.clear();
    QTextStream in(&f);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
            m_grid.append(line);}
    f.close();
    if (!m_grid.isEmpty())
    {
        int len = m_grid[0].size();
        for (const auto &currentLen : m_grid)
        {
            if (currentLen.size() != len) {
                qWarning() << "Check the file, the lines have different lengths";
                m_grid.clear();
                return;
            }
        }
    }
}

const QVector<QString> &labirint::grid() const
{
    return m_grid;
}

int labirint::rows() const
{
    return m_grid.size();
}

int labirint::collumns() const
{
    if (m_grid.isEmpty()) {
        return 0;
    } else {
        return m_grid[0].size();
    }
}

char labirint::cell(int row, int coll) const
{
    if (row<0 || row>=rows() || coll<0 || coll>=collumns())
        return '0';
    return m_grid[row][coll].toLatin1();
}

bool labirint::valid() const
{
    return !m_grid.isEmpty();
}




