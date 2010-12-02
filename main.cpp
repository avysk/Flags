#include <QApplication>
#include "worker.h"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        app.setApplicationName("Example");

        Worker w;
        w.show();

        return app.exec();
}
