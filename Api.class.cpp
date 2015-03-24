#include "includes/api.class.hpp"

Api::Api( void ) {}

Api::Api( Api const & src ) { *this = src; }

Api & Api::operator=( Api const & rhs ) {
	if (this != &rhs)
	{

	}
	return (*this);
}