#pragma once
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>

#include <QString>
#include <sstream>
#include <string>

class Function {
public:
  Function(){};
  ~Function(){};

protected:
  QString replace_id_staion(QString &raw_str);
  QString replace_raw_text(QString &raw_str);
};
