#include <QApplication>
#include "mode.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mode mode;
    mode.show();
    return app.exec();
}
