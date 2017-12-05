#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include "cell.h"
#include "row.h"

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = 0);
    ~Page();
    int height() const {return m_printer->height();}
    int width() const {return m_printer->width();}
    int getCurrentPage() const {return m_currentPage;}
    void newPage(){m_printer->newPage();}
    void draw();

private:
    QPainter *m_painter;
    QPrinter *m_printer;
    int m_currentPage;
    float m_posY;

signals:

public slots:
};

#endif // PAGE_H
