#include "script.h"
#include <iostream>
#include <cstdio>
#include <mruby.h>
#include <mruby/compile.h>

Script *Script::_self = 0;

Script::Script() {
  this->mrb = mrb_open();
}

Script::~Script() {
  std::cout << "Finalizando Script" << std::endl;
  mrb_close(this->mrb);
}

void Script::leerScript(const char *file) {
  FILE* fp = fopen(file, "r");
  mrb_load_file(this->mrb, fp);
  //mrb_print_backtrace(this->mrb);
}

void Script::exec(const char *str) {
  mrb_load_string(this->mrb, str);
}
Script* Script::instancia() {
  if(_self == 0){
    _self = new Script;
  }
  return _self;
}


