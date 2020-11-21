#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QColor>
#include "AVL.h"


class DrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawArea(AVL<int> *avl, QWidget *parent = nullptr);

    //методы для автоматического изменения размера картинки
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void autoSize();
    void callRepaint();

    //метод для установки дерева
    void setTree(AVL<int> *tree);

    //методы, рисующие дерево
    void draw(QPainter *painter, double &scale);
    void recursiveDraw(Node<int> *node);

protected:
    //этот метод вызывается для рисования
    void paintEvent(QPaintEvent *event) override;

private:
    AVL<int> *avl;
    double scale;
    QPen pen;
    QBrush brush;
    QColor backgroundColor;
    QColor textColor;
};

#endif // DRAWAREA_H
