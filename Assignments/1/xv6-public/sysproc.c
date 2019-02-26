#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"



int total_syscalls=29;


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_toggle(void)
{
  TRACE=(TRACE+1)%2;
  
  if(TRACE==1){
    for(int i=0;i<total_syscalls;i++){
      count_sys[i]=0; 
    }
  }
  return(TRACE);
}

int
sys_print_count(void)
{
  const char* sys_calls_xv6[]={
  "sys_fork",
  "sys_exit",
  "sys_wait",
  "sys_pipe",
  "sys_read",
  "sys_kill",
  "sys_exec",
  "sys_fstat",
  "sys_chdir",
  "sys_dup",
  "sys_getpid",
  "sys_sbrk",
  "sys_sleep",
  "sys_uptime",
  "sys_open",
  "sys_write",
  "sys_mknod",
  "sys_unlink",
  "sys_link",
  "sys_mkdir",
  "sys_close",
  "sys_toggle",
  "sys_print_count",
  "sys_halt",
  "sys_add",
  "sys_ps",
  "sys_send",
  "sys_recv",
  "sys_send_multi"
  };

  for(int i=0;i<total_syscalls;i++){
    if(count_sys[i]!=0){
      cprintf("%s %d\n",sys_calls_xv6[i],count_sys[i]);
    }
  }


  return(0);
}

int
sys_halt(void)
{
  outb(0xf4, 0x00);
  return 0;
}

int 
sys_add(void)
{
  int a1,b1;
  argint(0,&a1);
  argint(1,&b1);
  return(a1+b1);
}

int 
sys_ps(void)
{
  printProcesses();
  return(0);
}

int 
sys_send(void)
{
  int s_id;
  int r_id;
  char* mess;
  if(argint(0, &s_id) < 0)
    return -1;
  if(argint(1, &r_id) < 0)
    return -1;
  if(argstr(2, &mess) < 0)
    return -1;
  // cprintf("What's the matter %s haha",*mess);
  send(s_id,r_id, mess);
  return(0);
}


int 
sys_recv(void)
{
  char* mess;
  if(argstr(0, &mess) < 0)
    return -1;
  recv(mess);
  return(0);
} 

int 
sys_send_multi(void)
{
  
  return(0);

}