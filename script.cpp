#include "script.h"
#include <iostream>
#include <cstdio>
#include <mruby.h>
#include <mruby/compile.h>

Script *Script::_self = 0;

Script::Script() {
  this->mrb = mrb_open();
  this->mrbc = mrbc_context_new(this->mrb);
  this->mrbc->capture_errors = 1;
}

Script::~Script() {
  std::cout << "Finalizando Script" << std::endl;
  mrbc_context_free(mrb, this->mrbc);
  mrb_close(this->mrb);
}

void Script::leerScript(const char *file) {
  FILE* fp = fopen(file, "r");
  mrbc_filename(mrb, mrbc, file);
  mrb_load_file_cxt(mrb, fp, mrbc);
}

void Script::exec(const char *str) {
  mrb_load_string_cxt(this->mrb, str, this->mrbc);
}

Script* Script::instancia() {
  if(_self == 0){
    _self = new Script;
  }
  return _self;
}


