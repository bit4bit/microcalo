#ifndef COLISION_UTIL_H
#define COLISION_UTIL_H

class Circular
{
 public:
  /**
   *se centra  con respecto al objeto
   */
  Circular(int _x, int _y, int _radio)
  {
    x = _x;
    y = _y;
    radio = _radio;
  }
  int x;
  int y;
  int radio;
};


#endif
