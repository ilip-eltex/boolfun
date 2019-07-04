#include <iostream>

#include "test_api_header.h"
#include "test_private_header.h"

int main()
{
  std::cout << test_api_counter << inner_counter << std::endl;
}