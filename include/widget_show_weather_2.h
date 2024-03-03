#pragma once
#include <QWidget>
#include <QTime>
#include <utility>
#include <QEvent>
#include <QTimer>

namespace Ui {
    class Widget_Show_Weather_2;
}

class Widget_Show_Weather_2 : public QWidget {
    Q_OBJECT

  public:
    explicit Widget_Show_Weather_2 (QWidget* parent = nullptr);
    ~Widget_Show_Weather_2 ();
    void set_Label_Name_Airport (std::string&& in_str_Label_Name_Airport);
    void set_Label_Text_Raw_METAR (std::string&& in_str_Label_Text_Raw_METAR);
    void set_Label_Text_METAR (std::string&& in_str_Label_Text_METAR);
    void set_Label_Text_Raw_TAF (std::string&& in_str_set_Label_Text_Raw_TAF);
    void set_Label_Text_TAF (std::string&& in_str_Label_Text_TAF);

  protected:
    void showEvent (QShowEvent* event) override;

  private:
    Ui::Widget_Show_Weather_2* ui;
    QTimer* timer_close_weather;
};
