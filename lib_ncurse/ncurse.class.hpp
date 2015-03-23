#include "../includes/api.class.hpp"

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class lib_ncurse : public api
{
	public:
		lib_ncurse();
		~lib_ncurse();
};
