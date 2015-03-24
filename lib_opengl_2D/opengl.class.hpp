#include "../includes/api.class.hpp"

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class lib_opengl : public api
{
	public:
		lib_opengl();
		~lib_opengl();
};
