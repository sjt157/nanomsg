#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<nanomsg/nn.h>
#include<nanomsg/pubsub.h>

void usage(const char *name)
{
	fprintf(stderr,"%s [bind url]n",name);	
}

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		usage(argv[0]);
		exit(-1);
	}
	
	const char *url=argv[1];
	int sock=nn_socket(AF_SP,NN_PUB);
	if(sock<0)
	{
		fprintf (stderr, "nn_socket failed: %sn", nn_strerror (errno));
                 exit(-1);
	}
	if(nn_bind(sock,url)<0)
	{
		fprintf(stderr,"nn_bind failed:%sn",nn_strerror(errno));
		exit(-1);
	}

	while(1)
	{
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		char *text=asctime(timeinfo);
		int textLen=strlen(text);
		text[textLen-1]=' ';
		printf("SERVER:PUBLISHING DATE %sn",text);
		nn_send(sock,text,textLen,0);
		sleep(1);
	}
	return 0;

}
