#pragma once

#include <QDateTime>
#include <QString>
#include <QTextStream>

class Function {
  public:
    Function (){};
    ~Function (){};

  protected:
    QString replace_id_staion (QString& _raw_str);
    QString replace_raw_text (QString& _raw_text);
    QString replace_time (QString& _bulletin_time);
    QString replace_change_indicator (QString& _change_indicator);
    //    QString time_becoming () const;
    //    QString probability () const;
    //    QString wind_dir_degrees () const;
    //    QString wind_speed_kt () const;
    //    QString wind_gust_kt () const;
    //    QString wind_shear_hgt_ft_agl () const;
    //    QString wind_shear_dir_degrees () const;
    //    QString wind_shear_speed_kt () const;
    //    QString visibility_statute_mi () const;
    //    QString altim_in_hg () const;
    //    QString vert_vis_ft () const;
    //    QString wx_string () const;
    //    QString not_decoded () const;
};
