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
void udp()
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
	struct sockaddr_in sa;
	struct in_addr ip;
	char str[INET_ADDRSTRLEN];
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

	f = fopen("/proc/net/udp","r");
	fseek(f,110,SEEK_SET);//ignore first line
	while(fscanf(f,"%s",Linetcp)!=EOF){		
	   if(strlen(Linetcp)==13 ){
		if(count%3==0) printf("udp  ");
		count++;
		token = strtok(Linetcp,colon);//separate colon
				
		//inet_pton(AF_INET,token,&(sa.sin_addr));//change
		//inet_ntop(AF_INET,&(sa.sin_addr),str,INET_ADDRSTRLEN);//change
		ip.s_addr = (int)strtol(token,NULL,16);
	//	sa.sin_family = AF_INET;
		sa.sin_addr = ip;
		inet_ntop(AF_INET,&(sa.sin_addr),str,INET_ADDRSTRLEN);//to decimal
			
		printf("%s",str);
		printf(":");
		token = strtok(NULL, colon);
		portnum = (int)strtol(token,NULL,16);
		printf("%ld ",portnum);

		printf("        ");
	    }	

	  if(strlen(Linetcp)==5){//inode
		count++;
//		printf("inode=%s",Linetcp);
		dirp = opendir("/proc/");
		while((direntp = readdir(dirp))!=NULL){
			if(isdigit(*(direntp->d_name))){//proc
				//printf("\n%s",direntp->d_name);
//				strcat("/proc/",(direntp->d_name));
				strcpy(fr,"/proc/");
				strcat(fr,(direntp->d_name));
				strcat(fr,"/fd/");///proc/[pid]/fd
				//printf("%s\n",fr);
			//	oopen = fopen(fr,"r");
			//	if(oopen==NULL){
			//		printf("XXXXX");
			//	}
			//	while(fscanf(oopen,"%s",find)!=EOF){
			//		printf("%s",find);	
			//
			//		}
				DIR *dir;
				struct dirent *ptr;
				dir = opendir(fr);
				while((ptr = readdir(dir)) !=NULL){
			//		printf("\n%s",ptr->d_name);
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
						
							fclose(commd);





						}

					}
				}
				closedir(dir);
				//printf("%s\n",path);

			
				
			}
		}
		closedir(dirp);

	   
	 	 if(count%3==0){
		  	 printf("\n");
	  	 }

	  }
	   
	}
	
	fclose(f);
//	return 0;
}

