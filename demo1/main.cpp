#include "demo1.h"
#include <QtWidgets/QApplication>
#include "QWKWidgets/qwkwidgetsglobal.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QApplication app(argc, argv);
    demo1 window;
    window.show();
    return app.exec();
}
