#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QAction>
#include <QTextEdit>

#include "drawarea.h"
#include "AVL.h"
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //Кнопки
    QPushButton *deleteButton;
    QPushButton *insertButton;

    //Поля для ввода значения, которое нужно удалить либо вставить в дерево
    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;

    QTextEdit *treeActions;

    QScrollArea *treeScrollArea;

    QVBoxLayout *mainLayout;

    DrawArea *drawArea;

    AVL<int> *avl;

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void insertClicked() const;
    void deleteClicked() const;

};
#endif // MAINWINDOW_H
