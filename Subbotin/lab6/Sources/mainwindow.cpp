#include "mainwindow.h"
#include <QTime>
#include <QCoreApplication>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->avl = new AVL<int>;

     //Создаем кнопки
     deleteButton = new QPushButton("Удалить", this);
     insertButton = new QPushButton("Вставить", this);
     insertValueLineEdit = new QLineEdit;
     deleteValueLineEdit = new QLineEdit;
     treeActions = new QTextEdit;

     //Задаем параметры для кнопок и полей
     deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     insertValueLineEdit->setFixedWidth(200);
     deleteValueLineEdit->setFixedWidth(200);
     insertValueLineEdit->setValidator(new QIntValidator(-2147483648, 2147483647, this));
     deleteValueLineEdit->setValidator(new QIntValidator(-2147483648, 2147483647, this));
     treeActions->setFixedWidth(700);
     treeActions->setFixedHeight(200);
     treeActions->setReadOnly(true);

     // Связываем слоты с сигналами кнопок
     connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
     connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
     connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
     connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

     //Создаем слой для кнопок и добавляем туда кнопки
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(deleteButton);
     buttonLayout->addWidget(deleteValueLineEdit);
     buttonLayout->addWidget(insertButton);
     buttonLayout->addWidget(insertValueLineEdit);
     buttonLayout->addStretch(10);


     //Создаем пространство для отрисовки дерева
     drawArea = new DrawArea(this->avl);

     treeScrollArea = new QScrollArea;
     treeScrollArea->setWidget(drawArea);
     treeScrollArea->installEventFilter(drawArea);

     //Создаем основной слой
     mainLayout = new QVBoxLayout;
     mainLayout->addWidget(treeScrollArea);
     mainLayout->addLayout(buttonLayout);
     mainLayout->addWidget(treeActions);

     //Создаем основное окно
     centralWidget = new QWidget(this);
     centralWidget->setLayout(mainLayout);
     this->setCentralWidget(centralWidget);
     this->setMinimumHeight(600);
     this->setMinimumWidth(700);
     this->setWindowTitle("AVL-tree");

     this->show();
}

MainWindow::~MainWindow()
{
    delete drawArea;
    delete deleteButton;
    delete insertButton;
    delete treeScrollArea;
    delete avl;
    delete centralWidget;
}

//функция для задержки времени, чтобы можно было видеть шаги
void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// метод, который вызывается при нажатии на кнопку delete
void MainWindow::deleteClicked() const {
    //считываем значение, которое хотим удалить
    QString value = deleteValueLineEdit->text();

    //проверка на некорректный ввод
    if(value=="" || value.contains(" ") || value.toLongLong() < INT_MIN || value.toLongLong() > INT_MAX){
        treeActions->append("Ваше значение не входит в int!");
        deleteValueLineEdit->setText("");
        return;
    }

    int val = value.toInt();

    //на время отработки алгоритма блокируем все кнопки и поля, чтобы ничего не сломать
    deleteValueLineEdit->setReadOnly(true);
    insertValueLineEdit->setReadOnly(true);
    deleteButton->setEnabled(false);
    insertButton->setEnabled(false);

     //инициализируем переменные для хранения промежуточного состояния дерева и сообщений о действиях
    std::vector<AVL<int>> trees;
    std::vector<std::string> messages;

    //вызываем метод, который производит сам алгоритм и записывает промежуточные результаты в соответствующие переменные
    avl->deleteValue(val, trees, messages);

    //производим отображение всех шагов алгоритма
    for(unsigned int i = 0; i<messages.size(); i++){
        treeActions->append(QString::fromStdString(messages[i]));
        drawArea->setTree(&trees[i]);
        drawArea->repaint();
        delay();
    }

    //после отработки алгоритмов возвращаем кнопки и поля в рабочее состояние
    deleteValueLineEdit->setText("");
    deleteValueLineEdit->setReadOnly(false);
    insertValueLineEdit->setReadOnly(false);
    deleteButton->setEnabled(true);
    insertButton->setEnabled(true);
}


void MainWindow::insertClicked() const {
    //считываем значение, которое хотим вставить
    QString value = insertValueLineEdit->text();

    //проверка на некорректный ввод
    if(value=="" || value.contains(" ") || value.toLongLong() < INT_MIN || value.toLongLong() > INT_MAX){
        treeActions->append("Ваше значение не входит в int!");
        insertValueLineEdit->setText("");
        return;
    }

    int val = value.toInt();

    //на время отработки алгоритма блокируем все кнопки и поля, чтобы ничего не сломать
    deleteValueLineEdit->setReadOnly(true);
    insertValueLineEdit->setReadOnly(true);
    deleteButton->setEnabled(false);
    insertButton->setEnabled(false);

    //инициализируем переменные для хранения промежуточного состояния дерева и сообщений о действиях
    std::vector<AVL<int>> trees;
    std::vector<std::string> messages;

    //вызываем метод, который производит сам алгоритм и записывает промежуточные результаты в соответствующие переменные
    avl->insertValue(val, trees, messages);

    //производим отображение всех шагов алгоритма
    for(unsigned int i = 0; i<messages.size(); i++){
        treeActions->append(QString::fromStdString(messages[i]));
        drawArea->setTree(&trees[i]);
        drawArea->repaint();
        delay();
    }

    //после отработки алгоритмов возвращаем кнопки и поля в рабочее состояние
    insertValueLineEdit->setText("");
    deleteValueLineEdit->setReadOnly(false);
    insertValueLineEdit->setReadOnly(false);
    deleteButton->setEnabled(true);
    insertButton->setEnabled(true);
}

//этот метод предназначен для автоматического изменения размера отображаемой картинки
void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    this->drawArea->callRepaint();
}




