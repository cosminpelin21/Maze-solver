#ifndef LABIRINT_H
#define LABIRINT_H
#include <QString>
#include <QVector>

class labirint
{
private:
    QVector<QString> m_grid;
public:
    labirint();
    void readFile(const QString &file);
    const QVector<QString>& grid() const;
    int rows() const;
    int collumns() const;
    char cell(int row, int coll) const;
    bool valid() const;
};

#endif // LABIRINT_H
