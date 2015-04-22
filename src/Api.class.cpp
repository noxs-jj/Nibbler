#include "../includes/api.class.hpp"

Api::Api( void ) {}
Api::Api( Api const & src ) { *this = src; }
Api::~Api( void ) {}
Api & Api::operator=( Api const & rhs ) { static_cast<void>(rhs); return (*this); }
