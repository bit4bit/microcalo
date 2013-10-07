#include "carray.h"
#include <mrubybind.h>
#include <iostream>

template <class T>
static CArray<T>* carray_new() {
  return new CArray<T>;
}

static CArrayString* carray_string_new() {
  return new CArrayString;
}

template <typename T>
int CArray<T>::size() {
  return std::vector<T>::size();
}

template <class T>
void CArray<T>::bindingScript(mrb_state *mrb) {
  mrubybind::MrubyBind b(mrb);
  b.bind_class("CArray", carray_new<T>);
  b.bind_instance_method("CArray", "<<", &CArray<T>::push_back);
  b.bind_instance_method("CArray", "push", &CArray<T>::push_back);
  b.bind_instance_method("CArray", "clear", &CArray<T>::clear);
  b.bind_instance_method("CArray", "size", &CArray<T>::size);

  b.bind_class("CArrayString", carray_string_new);
  b.bind_instance_method("CArrayString", "<<", &CArrayString::push_back);
  b.bind_instance_method("CArrayString", "push", &CArrayString::push_back);
  b.bind_instance_method("CArrayString", "clear", &CArrayString::clear);
  b.bind_instance_method("CArrayString", "size", &CArrayString::size);
}

template class CArray<std::string>;
