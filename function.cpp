#include "function.h"

#include <QTextStream>

QString Function::replace_id_staion(QString &id_str) {
  if (id_str == "UUWW") {
    id_str = "ВНУКОВО";
  };
  if (id_str == "UUEE") {
    id_str = "ШЕРЕМЕТЬЕВО";
  };
  if (id_str == "UUDD") {
    id_str = "ДОМОДЕДОВО";
  };
  return id_str;
}

QString Function::replace_raw_text(QString &raw_str) {
  raw_str.replace("TEMPO", "\n       TEMPO ");
  raw_str.replace("BECMG", "\n       BECMG ");
  raw_str.replace("FM", "\n       FM ");

  return raw_str;
}
