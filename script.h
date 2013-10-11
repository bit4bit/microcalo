#ifndef SCRIPT_H
#define SCRIPT_H

#include "bindingscript.h"

class Script
{
 public:
  static Script* instancia();
  static void cerrar() { delete _self;}
  void leerScript(const char*);
  void exec(const char*);
  mrb_state* obState() { return this->mrb; }


 protected:
  Script();
  ~Script();

 private:
  static Script *_self;
  mrb_state *mrb;
  mrbc_context *mrbc;
  
};

#endif
