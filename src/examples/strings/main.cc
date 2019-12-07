#include <iostream>

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"

int main(int argc, char** argv) {
  base::string16 str16 = L"This is a test string.";
  std::cout << L"Output string16: " << str16.c_str() << std::endl;

  std::string str = base::WideToUTF8(str16);
  std::cout << L"Output string: " << str.c_str() << std::endl;
  
  return 0;
}
