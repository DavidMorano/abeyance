/* main */

#include	<sys/types.h>
#include	<unistd.h>
#include	<iostream>

int  main(int,const char *const *,const char *const *) {
	int	sid = getsid(0) ;
	std::cout << sid << '\n' ;
}


