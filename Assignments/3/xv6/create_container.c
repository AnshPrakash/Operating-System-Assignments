#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"


char*
my_fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
my_ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", my_fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %d %d %d\n", my_fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}


void
init_containers_resources(){
  //setting up the file system
  mkdir("c1");
  mkdir("c2");
  mkdir("c3");
  mkdir("c4");
  mkdir("c5");
  mkdir("c6");
  mkdir("c7");
  mkdir("c8");
  mkdir("c9");
  mkdir("c10");
  mkdir("c11");
  mkdir("c12");
  mkdir("c13");
  mkdir("c14");
  mkdir("c15");
  mkdir("c16");
  mkdir("c17");
  mkdir("c18");
  mkdir("c19");
  mkdir("c20");
}


//convert int to string
void
itoa(int num , char* ret)
{
  int rem, len = 0;
  int n = num;
  while(n!=0){
    len++;
    n = n/10;
  }
  for(int i=0;i<len;i++){
    rem = num%10;
    num = num/10;
    ret[len - (i+1)] =rem +'0';
  }
  ret[len] = '\0';
}

void
join_container_wrapper(int i){
  char cid_s[4];
  cid_s[0] = 'c';
  char  conv[3];
  itoa(i,conv);
  cid_s[1] = conv[0];
  cid_s[2] = conv[1];
  cid_s[3] = '\0';
  chdir(cid_s);
  join_container(i);
}

void 
create_file(char* filename)
{
  int fd;
  if((fd = open(filename,O_CREATE))<0){
    printf(1," not able to create the file\n");
  }
  close(fd);
}


/*
 *   mode : rdonly 0
 *        : wronly 1
 *        : rdwr 2
 */     
int 
open_file(char* filename,int mode)
{ 
  int fd = -1;
  if(mode == 0 ){
    fd = open(filename,O_RDONLY);
  }
  else if(mode == 1){
    fd = open(filename,O_WRONLY);
  }
  else if(mode == 2){
    fd = open(filename,O_RDWR);
  }

  if(fd<0){
      printf(1," not able to create the file\n");
  }
  return(fd);
}

int main(void)
{

  init_containers_resources();
	create_container(1);

  // int fd;
  // if((fd = open("hello",O_CREATE|O_RDWR))<0){
  //   printf(1," not able to create the file\n");
  // }
  // char raw[5] = "ansh\n";
  // int n =5;
  // write(fd,raw,n);
  // close(fd);
  // char r[3];
  // itoa(1,r);
  // printf(0,"%s\n",r);
  // my_ls(".");
	// create_container(2);
	// create_container(3);
	// newls();
	
	// destroy_container(1);
	int pid = fork();
	if(pid == 0){
		join_container_wrapper(1); // called only by child created by preceeding fork call .
		// fork();
    create_file("hello");
    int fd;
    fd =open_file("hello",2);
    char raw[5] = "ansh\n";
    int n =5;
    write(fd,raw,n);
    close(fd);
    my_ls(".");
		// ps();
		// leave_container();
		// ps();		
	}

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
	wait();
	exit();
}

