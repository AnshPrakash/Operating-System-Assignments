#include "types.h"
#include "stat.h"
#include "user.h"



int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	
	float variance = 0.0;

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]=c-'0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
  
  	//----FILL THE CODE HERE for unicast sum and multicast variance
  	const int p=20;// NUmber of child processes
  	int cid=-2;
  	int idx=-1;
  	int parnet_pid=getpid();
  	for(int i=0;i<p;i++){
  		cid=fork();
  		if(cid==0){
  			//child process
  			idx=i;
	  		int localsum=0;
	  		int last=(idx + 1) * size/p;
	  		if(idx==p-1){
	  			last=size;
	  		}
	  		for (int i =idx*(size/p); i<last; ++i){
	  			localsum+=arr[i];
	  		}
	  		char *msg = (char *)malloc(8);
	  		int mypid=getpid();
	  		itoa(localsum,msg);
	  		
	  		send(mypid,parnet_pid,msg);
	  		exit();
	  	}
  	}
  	
	for(int i=0;i<p;i++){
		char *msg_r= (char*)malloc(8);
		recv(msg_r);
		// printf(1,"Parent %s\n",msg_r);
		tot_sum+=atoi(msg_r);
	}



  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	else{ //mulicast variance
		printf(1,"Variance of array for file %s is %d\n", filename,(int)variance);
	}
	exit();
}
