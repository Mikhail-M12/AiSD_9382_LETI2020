#include "cw.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cw w;
	w.show();
    return a.exec();
}
