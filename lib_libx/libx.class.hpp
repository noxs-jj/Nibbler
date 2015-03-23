#include "../includes/api.class.hpp"

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class lib_libx : public api {
public:
	lib_libx( void );
	lib_libx( lib_libx const &bsrc );
	lib_libx & operation=(lib_libx const &brhs);
	~lib_libx();

private:
	

};
