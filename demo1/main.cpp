#include "demo1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    demo1 window;
    window.show();
    return app.exec();
}
