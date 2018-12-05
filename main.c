#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(){
  key_t key;
  int shmid;
  char * data;
  int mode;
  char line[200];
  //Step 1
  if((key = ftok("main.c",'R')) == -1 ){
    perror("ftok");
    exit(1);
  }
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  //pointer to shared memory segment
  data = shmat(shmid,(void*)0,0);
  //Step 2
  if(!data[0]){
    printf("Segment was just created!\n");
  }
  else{
    printf("Contents of shared segment: %s\n",data);
  }
    //Step 3
    printf("Would you like to change the data in the segment? enter y or n\n");
    fgets(line,200,stdin);
    if (!strcmp(line,"y\n")){
      printf("New string:\n");
      fgets(line,200,stdin);
      strcpy(data,line);
    }
  printf("Updated contents of shared segment: %s\n",data);
  printf("Would you like to delete the segment? enter y or n\n");
  fgets(line,200,stdin);
  if(!strcmp(line,"y\n")){
    shmdt(data);
    shmctl(shmid,IPC_RMID,NULL);
    printf("Deleted shared segment.\n");
  }
  return 0;


}
