#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "tcp.c"
#include "tcp6.c"
#include "udp.c"
#include "udp6.c"

int main(int argc, char *argv[]){
	
	int opt;
	int option_index = 0;
	char *optstring = ":tu";
	static struct option long_options[] = {
		{"tcp",0,NULL,'t'},
		{"udp",0,NULL,'u'},
		
	};
	while((opt = getopt_long(argc,argv,optstring,long_options,&option_index))!=-1){
	      if(opt=='t'){
		printf("List of TCP connctions:\n");
		printf("Proto  Local Address    Foreign Address    PID/Program name and arguments\n");
		tcp();
		tcp6();
		printf("\n");
		return 0;
		}

	      else if(opt=='u'){
		printf("List of UDP connections:\n");
		printf("Proto  Local Address    Foreign Address    PID/program name and arguments\n");
		udp();
		udp6();
		printf("\n");
		return 0;
		}
	      
	}
	 printf("List of TCP connctions:\n");
	 printf("Proto  Local Address    Foreign Address    PID/Program name and arguments\n");
         tcp();
         tcp6();
         printf("\n");

	 printf("List of UDP connections:\n");
         printf("Proto  Local Address    Foreign Address    PID/program name and arguments\n");
         udp();
         udp6();
         printf("\n");



}
