#include "quad_sim.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    quad_sim w;
    w.show();

    return a.exec();
}
