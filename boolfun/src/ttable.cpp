#include "ttable.h"
using namespace std;

ttable::ttable(unsigned char n) {
	this->_values.reserve( static_cast<size_t>(pow(2,n)) );
		 
}

bool ttable::set (std::vector<bvect32> arr) {
	if ( arr.size() >= pow(2,n) )
		return false;
	this->_values = arr;
	return true;
}

bvect32 ttable::get () {
	return this->_values;
} 


