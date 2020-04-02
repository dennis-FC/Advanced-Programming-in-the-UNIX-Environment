#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

/*void constring(char s[],char t[], char q[]){
	int i ,j;
	for (i =0;s[i]!='\0';i++){
		q[i] = s[i];
	}
	for (j= 0;t[j]!='\0';j++){
		q[i+j] = t[j];
	}
	q[i+j] = '\0';
}
*/
void udp6()
{
	char ch;
	char Linetcp[1000];
	char find[1000];
	char scan[1000];
	FILE *f;
	FILE *oopen;
	FILE *commd;
	char *token;
	char colon[2]=":";//colon
	int count = 0;
	struct sockaddr_in6 sa;
	struct in6_addr ip;
	char str[INET6_ADDRSTRLEN];
	long portnum;
	DIR *dirp;;
	struct dirent *direntp;
	char s[100];
	char q[100];
	char t[200];
	char path[500];
	char pathpath[500];
	char pid[256];
	char fr[50];

	f = fopen("/proc/net/tcp6","r");
	fseek(f,140,SEEK_SET);//ignore first line
	while(fscanf(f,"%s",Linetcp)!=EOF){		
	   if(strlen(Linetcp)==37 ){
		if(count%3==0) printf("udp6  ");
		count++;
		token = strtok(Linetcp,colon);//separate colon
		//ip.s6_addr[16] = (int)strtol(token,NULL,16);
		for (int i = 0;i<16;i++){
			char s6[8] = "";
			strncpy(s6,token+i*2,2);
			ip.s6_addr[i] = (int)strtol(token,NULL,16);
		}


		sa.sin6_addr = ip;
		inet_ntop(AF_INET6,&(sa.sin6_addr),str,INET6_ADDRSTRLEN);
			
		printf("%s",str);
		printf(":");
		token = strtok(NULL, colon);
		portnum = (int)strtol(token,NULL,16);
		printf("%ld ",portnum);

		printf("              ");
	    }	

	  if(strlen(Linetcp)==5){//inode
		count++;
		//printf("inode=%s",Linetcp);
		dirp = opendir("/proc/");
		while((direntp = readdir(dirp))!=NULL){
			if(isdigit(*(direntp->d_name))){//proc
				//printf("\n%s",direntp->d_name
				strcpy(fr,"/proc/");
				strcat(fr,(direntp->d_name));
				strcat(fr,"/fd/");///proc/[pid]/fd
				//printf("%s\n",fr);
	//			oopen = fopen(fr,"r");
	//			if(oopen==NULL){
	//				printf("XXXXX");
	//			}
			
				DIR *dir;
				struct dirent *ptr;
				dir = opendir(fr);
				while((ptr = readdir(dir)) !=NULL){
				//	printf("\n%s",ptr->d_name);
				 	char pp[50];
					strcpy(pp,fr);
					strcat(pp,ptr->d_name);
				//	printf("%s\n",pp);
					if(isdigit(*(ptr->d_name))){
						readlink(pp,pid,256);
					//	printf("%s\n",pp);
						//printf("%s\n",Linetcp);
						if(strstr(pid,Linetcp)){
							
							printf("%s",direntp->d_name);
							printf("/");
							char cmd[50];
							strcpy(cmd,"/proc/");
							strcat(cmd,direntp->d_name);
							strcat(cmd,"/comm");
							commd = fopen(cmd,"r");
							while(fscanf(commd,"%s",scan)!=EOF){
								printf("%s",scan);
							}





						}

					}
				}
				closedir(dir);
				//printf("%s\n",path);

			
				
			}
		}
		closedir(dirp);

	  //	printf("%d",count); 
	 	// if(count%3==0){
		  	 printf("\n");
	  	// }

	  }
	   
	}
	
	fclose(f);
//	return 0;
}

