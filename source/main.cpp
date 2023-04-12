#include <QApplication>

#include "./include/lb_weather.h"
#include "./include/widget.h"

int main (int argc, char* argv [])
{
    QApplication a (argc, argv);

    Widget w;
    w.setWindowIcon (QIcon (":/resource/meteo.ico")); // Значок для окна

    w.show ();
    return a.exec ();
}
