#include "../includes/circle.test.hpp"

void circle::draw()
{
    std::cout << "   ###   " << std::endl;
    std::cout << "  #   #  " << std::endl;
    std::cout << " #     # " << std::endl;
    std::cout << " #     # " << std::endl;
    std::cout << "  #   #  " << std::endl;
    std::cout << "   ###   " << std::endl;
}
 
extern "C"
{
    circle	*make_circle()
    {
		return new circle();
    }
}