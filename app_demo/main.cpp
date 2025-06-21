#include "stdafx.h"
#include "app_demo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app_demo window;
    window.show();
    return app.exec();
}
