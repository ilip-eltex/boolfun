#include <iostream>

#include "test_api_header.h"
#include "test_private_header.h"
#include "GF.h"


using bf::inner_counter;

// artem
auto field = bf::get_field(10);
bf::bvect32 a = 1, b = 3;
auto c = field->mult(a, b);

int main()
{
  std::cout << bf::test_api_counter << inner_counter << std::endl;

  return 0;
}