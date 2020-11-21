#include "drawarea.h"


DrawArea::DrawArea(AVL<int> *avl, QWidget *parent) : QWidget(parent),avl(avl), scale(1.0), backgroundColor(Qt::white), textColor(Qt::black){}

void DrawArea::setTree(AVL<int> *tree){
    this->avl = tree;
}

void DrawArea::paintEvent(QPaintEvent *){

    if (this->avl->isEmpty())
        return;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(this->textColor);

    painter.setBrush(brush);
    painter.setPen(pen);

    draw(&painter, this->scale);

    this->autoSize();
}

void DrawArea::draw(QPainter *painter, double &scale){
    if (avl->getRoot() == nullptr)
        return;

    //Свойства для отрисовки дерева
    avl->painter = painter;
    avl->painter->setFont(QFont("Times", 12*scale, QFont::Normal));

    //Размерности дерева и его элементов
    avl->scale = scale;
    avl->nodeRadius = 20*scale;

    //отступы между вершинами по горизонтали и вертикали
    avl->xspace = avl->nodeRadius;
    avl->yspace = avl->nodeRadius * 2;


    //Перед тем, как начать рисовать, надо убедиться, что все вершины имеют позицию по x=0
    avl->resetNodePosition(avl->getRoot());

    //для самой левой вершины делаем отступ равным радиусу вершины * 2
    Node<int> *leftmost = avl->getLeftmostNode(avl->getRoot());
    leftmost->x = avl->nodeRadius * 2;

    //рекурсивно отрисовывем дерево, начиная с корня
    recursiveDraw(avl->getRoot());

}

void DrawArea::recursiveDraw(Node<int> *node){
    if(node == nullptr){
        return;
    }

    //рисуем левое поддерево
    this->recursiveDraw(node->leftChild);

    //узнаем уровень вершины(порядок от корня вниз)
    int level = avl->getNodeLevel(node);

    //ставим отступ по вертикали
    int y = level*avl->nodeRadius*2 + avl->yspace*(level-1);

    //если у вершины есть левый ребенок
    if(node->leftChild != nullptr){
        //ставим отступ по горизонтали, прибавляем к положению самой правой вершины левого поддерева, радиус + отступ
        node->x = avl->getPxLocOfLeftTree(node->leftChild) + avl->nodeRadius + avl->xspace;

        //строим отрезок между двумя точками: самой нижней точкой текующей вершины и самой верхней точкой левого ребенка
        avl->painter->drawLine(QPoint(node->x, y + avl->nodeRadius), QPoint(node->leftChild->x + 1, ((level+1)* avl->nodeRadius*2 + avl->yspace * level) - avl->nodeRadius));
    }
    else if(node->x == 0){
        //если у вершины нет левого ребенка и она имеет начальное положение
        //подвинем ее правее от самого первого предка(начиная с текующей вершины)
        node->x = avl->getPxLocOfAncestor(node) + avl->nodeRadius + avl->xspace;
    }

    //ставим цвета
    QBrush brush;
    brush.setColor(node->color);
    brush.setStyle(Qt::SolidPattern);
    avl->painter->setBrush(brush);

    //рисуем круг(вершину)
    avl->painter->drawEllipse(QPoint(node->x, y), avl->nodeRadius, avl->nodeRadius);

    //переменная для корректировки положения числа в зависимости от количества в нем знаков
    int textAdjuster;
    if(fabs(node->value) < 10){
        textAdjuster = 4;
    }
    else if(fabs(node->value) < 100){
        textAdjuster = 7;
    }
    else if(fabs(node->value) < 1000){
        textAdjuster = 12;
    }
    else {
        textAdjuster = 16;
    }

    //рисование числа
    avl->painter->drawText(QPoint(node->x - textAdjuster*scale, y+5*scale), QString::number(node->value));

    //рисование правого поддерева
    this->recursiveDraw(node->rightChild);

    //рисование отрезка между вершиной и его правым ребенком аналогично с левым отрезком
    if(node->rightChild != nullptr){
        avl->painter->drawLine(QPoint(node->x, y + avl->nodeRadius), QPoint(node->rightChild->x - 2, ((level + 1) * avl->nodeRadius * 2 + avl->yspace * level) - avl->nodeRadius));
    }
}


QSize DrawArea::sizeHint() const{
    return QSize(50,50);
}

QSize DrawArea::minimumSizeHint() const{
    return QSize(50,50);
}

void DrawArea::callRepaint(){
    if(this->avl->isEmpty()){
        return;
    }
    this->scale +=0.1;
    this->repaint();
    this->scale -=0.1;
    this->repaint();
}

void DrawArea::autoSize(){
    QSize size(avl->getTotalX(), avl->getTotalY());
    this->setMinimumSize(size);
    this->resize(size);
}


