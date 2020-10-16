#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
int main(int argc,char **argv){
	int sockfd, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
	using namespace std;
	string IP , file_name ,code;
	int PORT;
	ifstream script;
	if(argc ==1){
		cout<<"NO argument passed!!"<<endl<<"[Defalut]"<<endl<<"UR5 IP  : 192.168.10.102"<<endl<<"UR5 port : 30002"<<endl;
		IP = "192.168.10.102";
		PORT = 30002;
	}
	else if(argc==3){
		cout<<"[Setting Data]"<<endl<<" UR5 IP  : "<<argv[1]<<endl<<"UR5 port : "<<argv[2]<<endl;
		IP = argv[1];
		PORT = atoi(argv[2]);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		cout<<"Cannot create robot!!"<<endl;
		return -1;
	}
	
	if(!server){
		fprintf(stderr,"ERROR, no such host\n");
        exit(0);
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	server_addr.sin_port = htons(PORT);
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
		cout<<"Cannot conect robot!!"<<endl;
		return -1;
	}
	while(true){
		cout<<"To send script file name : ";
		getline(cin,file_name);
		script.open(file_name);
		code = "def myScript():\n";
		while(script.good()){
			string temp;
			getline(script,temp);
			code += "\t";
			code += temp;
			code += "\n";
		}
		if(script.eof())
			cout<<"Read all code"<<endl;
		else
			cout<<"File read error"<<endl;
		code += "end\n";
		cout<<"[Code]"<<endl;
		cout<<code<<endl;
		send(sockfd,code.c_str(),code.size()*sizeof(char),0);
		script.close();
	}
	return 0;
}