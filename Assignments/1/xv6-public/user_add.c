# include "types.h"
# include "user.h"


int
main(int argc,char* argv[])
{
	int ans=add(atoi(argv[1]),atoi(argv[2]));
	printf(1,"%d\n",ans);
	exit();
}