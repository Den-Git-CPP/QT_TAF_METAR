#include <QApplication>

#include "lb_weather.h"
#include "widget.h"

int main (int argc, char* argv [])
{
    QApplication a (argc, argv);
    Widget w;
    w.setWindowIcon (QIcon (":/resource/avia.png")); // Значок для окна

    w.show ();
    return a.exec ();
}