#include <iostream>

#include "test_api_header.h"
#include "test_private_header.h"

using bf::inner_counter;

int main()
{
  std::cout << bf::test_api_counter << inner_counter << std::endl;
}