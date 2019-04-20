#include "types.h"
#include "user.h"

int main(void)
{
	create_container(1);
	create_container(2);
	create_container(3);
	newls();
	destroy_container(1);
	// int pid = fork();
	// if(pid == 0){
	// 	join_container(1); // called only by child created by preceeding fork call .
	// 	// fork();
	// 	ps();
	// 	leave_container();
	// 	ps();		
	// }

	// fork();
	// join_container(1); // called only by child created by preceeding fork call .
	// fork();
	// join_container(1); // called only by child created by preceeding fork call .
	//  Testing of resource isolation 
	// fork();
	// join_container(2); // called only by child created by preceeding fork call .
	// fork ();
	// join_container (3); // called only by child created by preceeding fork call .
	/* - - - - - - - - - - PROCESS ISOLATION - - - - - - - - - - - - - - - - - - */
	// called by atmost one process in every container .
	// ps() ;
	// while(1);
	// wait();
	exit();
}