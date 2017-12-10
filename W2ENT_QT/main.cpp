#include "GUI_MainWindow.h"
#include <QApplication>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI_MainWindow w;
    w.show();
    w.initIrrlicht();

    if (QCoreApplication::arguments().size() > 1)
        w.loadMesh(QCoreApplication::arguments().at(1));

    return a.exec();
}
