#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 대화면 GUI 인스턴스 가동 및 출력
    MainWindow window;
    window.show();

    return app.exec();
}