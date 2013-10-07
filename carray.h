#ifndef CARRAY_H
#define CARRAY_H

#include <vector>
#include <mruby.h>
#include <string>
/**
 *Array para conectar cpp y mruby
 */

template <typename T>
class CArray : public std::vector<T>
{
 public:
  int size();
  static void bindingScript(mrb_state*);
};

class CArrayString : public CArray<std::string>
{

};
//typedef class CArray<std::string> CArrayString;
#endif
