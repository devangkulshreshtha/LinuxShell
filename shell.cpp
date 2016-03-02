#include<iostream>
#include<bits/stdc++.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<cstring>
using namespace std;

int makedirectory(string token, int sz){
	char path[100];
	//cout<<"in"<<endl;
	//int sz = tokens.size();
	int t=0;				
	for(t=0; t<sz; t++){
		(path[t]) = (char)token[t];
		//cout<<path[t]<<endl;
	}
	path[t-1] = '\0';
	const int dir_err = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//cout<<dir_err<<endl;
	if (-1 == dir_err)
	{
    		printf("Error creating directory!\n");
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[], char *envp[]){
	char c = '\0';
	char *buf=(char *)malloc(sizeof(char) * 100);
	string input = "";
	size_t size = 100;
	system("clear");
	//system("echo ##################Custom-Shell####################");
	printf("shell>");
	while(c != EOF) {
		c = getchar();
		int nooftokens = 0;
		input += c;
		if(c == '\n'){
			string tokens[10];
			int i=0;
			tokens[i] = strtok(&input[0]," ");
			//cout<<tokens[i]<<"0"<<endl;
			while(1){
				char*s=strtok(NULL, " ");
				if(s==NULL){
					//tokens[++i] = "_$_";
					break;
									
				}				
				tokens[++i] = s;							
				//cout<<tokens[i]<<"0"<<endl;
			}
			nooftokens = i;
			//cout<<nooftokens<<endl;
			if(tokens[0].compare("cd") == 0){				
				char path[100];
				//cout<<"in"<<endl;
				int sz = tokens[1].size();
				int t=0;				
				for(t=0; t<sz; t++){
				(path[t]) = (char)tokens[1][t];
				//cout<<path[t]<<endl;
				}
				path[t-1] = '\0';
				chdir(path);
				//cout<<			
			}
			else if(tokens[0].compare("pwd\n") == 0){
				getcwd(buf, size);
				cout<<buf<<endl;			
			}
			else if(tokens[0].compare("mkdir") == 0){
				int sz = tokens[1].size();				
				makedirectory(tokens[1], sz);				
				char path[100];
				//cout<<"in"<<endl;
				
				int t=0;				
				for(t=0; t<sz; t++){
				(path[t]) = (char)tokens[1][t];
				//cout<<path[t]<<endl;
				}
				path[t-1] = '\0';
				//const int dir_err = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				//cout<<dir_err<<endl;
				//if (-1 == dir_err)
				//{
    				//	printf("Error creating directory!\n");
				//}
			}
			else if(tokens[0].compare("exit\n") == 0){
				exit(1);			
			}
			else if(tokens[0].compare("rmdir") == 0){
				char path[100];
				//cout<<"in"<<endl;
				int sz = tokens[1].size();
				int t=0;				
				for(t=0; t<sz; t++){
				(path[t]) = (char)tokens[1][t];
				//cout<<path[t]<<endl;
				}
				path[t-1] = '\0';
				const int dir_err = rmdir(path);
				//cout<<dir_err<<endl;
				if (-1 == dir_err)
				{
    					printf("Error deleting directory!\n");
				}
			}
			else if(tokens[0].size()>=2){
				char path[100];
				//cout<<"in"<<endl;
				int sz = tokens[0].size();
				int t=0;				
				for(t=0; t<sz; t++){
				(path[t]) = (char)tokens[0][t];
				//cout<<path[t]<<endl;
				}
				if(path[t-1] == '\n')
					path[t-1] = '\0';
				pid_t pid;
				pid = fork();
				if(pid < 0){
					cout<<"Error executing the file (Could not fork() child)"<<endl;
				}
				else if(pid == 0){
					char executablename[100];
					int i=0;
					int sz1 = tokens[0].size();
					int t1=0;				
					for(t1=0; t1<sz1; t1++){
						(executablename[t1]) = (char)tokens[0][t1];
						//cout<<path[t]<<endl;
					}
					string filename="";
					char fname[100];
					filename = strtok(executablename,"/");
					//cout<<tokens[i]<<"0"<<endl;
					while(1){
						char*s=strtok(NULL, "/");
						if(s==NULL)
							break;
						filename += s;
					}
					int sz = filename.size();
					int t=0;				
					for(t=0; t<sz; t++){
						(fname[t]) = (char)filename[t];
						//cout<<path[t]<<endl;
					}
					//char newpath[1000];
					//char *pathvar;
     					//pathvar = getenv("PATH");
     					//strcpy(newpath, pathvar);
     					//strcat(newpath, ":u/userid/bin");
     					//cout<<setenv("PATH", newpath, 0)<<endl;
					//char* arg = executablename.c_str();
					//sz = tokens[1].size();
					//tokens[1][sz-1] = '\0';
					
					char* strn = const_cast<char *>(tokens[1].c_str());
					//char* flname = const_cast<char *>(filename.c_str());
					//cout<<nooftokens<<endl;
					char * myargv[100];
					int flagin = 0, flagout = 0;
					string redirect = ">";
					//cout<<tokens[2]<<endl;					
					int temptokens = nooftokens;
					//cout<<temptokens<<endl;
					int h;int hin;int reach;
					int flagpipe = 0, pipebreak;
					for(h=0; h<=temptokens; h++){
						//cout<<tokens[h]<<endl;
						sz = tokens[h].size();
						if(tokens[h][sz-1] == '\n')
							tokens[h][sz-1] = '\0';
						if(tokens[h][0] == '>'){
							flagout = 1;
							nooftokens = h-1;
							break;
						}
						if(tokens[h][0] == '<'){
							flagin = 2;
							hin = h;
							//nooftokens = h-1;
							//break;
						}
						if(tokens[h][0] == '|'){
							flagpipe ++;
							pipebreak = h;
							//cout<<pipebreak<<endl;
							//continue;
						}
						if(flagin != 2){
							char* strn = const_cast<char *>(tokens[h].c_str());
							myargv[h] = strn;
							reach = h;
						}//append(strn, myargv);
						else if(flagpipe != 0){
							myargv[h-flagpipe] = strn;
							
						}

					}
					//cout<<"----"<<tokens[pipebreak]<<endl;
					//for(int l=0; l<=reach; l++){
					//	cout<<myargv[l]<<endl;
					//}
					if(flagpipe != 0){
						//cout<<"in pipe"<<endl;
						int pipefd[2];
						pipe(pipefd);
						//	cout<<"Error executing pipe!"<<endl;
						//}
						if(true){
							//cout<<"in pipe1"<<endl;
							int istream = dup(0);
							//dup2(pipefd[0],0);
							//cout<<"in pipe2"<<endl;
							//int in = open("./mytst", O_RDONLY);
							int ostream = dup(1);
							
							//dup2(pipefd[1],1);
							//cout<<"in pipe3"<<endl;
							pid_t pids;
							char *args1[100];
							char *args2[100];
							for(int l=0; l<pipebreak; l++){
								args1[l] = myargv[l];
								//cout<<args1[l]<<endl;
							}
							args1[pipebreak] = '\0';
							int j=0;
							//cout<<"temptokens"<<temptokens<<endl;
							//cout<<myargv[pipebreak+1]<<endl;
							for(int l=pipebreak+1; l<=temptokens; l++, j++){
								args2[j] = myargv[l];
								//cout<<args2[j]<<endl;
							}
							args2[j] = '\0';
							pids = fork();
							
							if (pids == 0)
    						{
    							//cout<<"child"<<endl;
      							dup2(pipefd[1], 1);

      							close(pipefd[0]);
      							execvp(args1[0], args1);
    						}
  							else
    						{
    							wait(NULL);
    							//cout<<"parent"<<endl;
    							dup2(ostream, 1);
      							dup2(pipefd[0], 0);

      							close(pipefd[1]);
      							
      							execvp(args2[0], args2);
    						}
    					dup2(istream, 0);
    					//cout<<"back"<<endl;
						//fflush(stdout);
						}
					}
					if(flagin==2){
						strn = const_cast<char *>(tokens[hin+1].c_str());
						myargv[reach+1] = '\0';
						if(strn[tokens[hin+1].size()-1]=='\n'){
							strn[tokens[hin+1].size()-1]='\0';
						}
						if(flagout==1){
							char* strout = const_cast<char *>(tokens[temptokens].c_str());
							strout[tokens[temptokens].size()-1] = '\0';
							//cout<<strn<<endl;
							//cout<<strout<<endl;
							
							int in = open(strn, O_RDONLY);
							int out = open(strout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
							dup2(in, 0);
							dup2(out, 1);
							close(in);
							close(out);
							execvp(myargv[0], myargv);
							
						}
						else{
							int in = open(strn, O_RDONLY);
							dup2(in, 0);
							execvp(myargv[0], myargv);
							close(in);
						}
					}
					else{
					strn = const_cast<char *>(tokens[temptokens].c_str());
					//cout<<flag<<endl;
					myargv[nooftokens+1] = '\0';
					int fd = open(strn, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					//int in = open(strn, O_RDONLY);
					if(flagout == 1){
        				dup2(fd, 1);	
					}   // make stdout go to file
        			
					//cout<<myargv[2]<<endl;
					execvp(myargv[0], myargv);					
					close(fd);
					}
					//if(strcmp(strn,"")!=0){					
					//	char * myargv[] = {path,strn,'\0'};
					//	execvp(path, myargv);
					//}
					//else{
					//	char * myargv[] = {path,'\0'};
					//	execvp(path, myargv);
					//}
					//char *argv[] = { 'a', 'l', 't', '\0' };					
					
					//execlp(path, filename.c_str(), NULL);
					//cout<<"Doing fork"<<endl;
				}
				else{ 
					waitpid(-1, NULL, 0);
				}
			}
			input = "";
			
			printf("shell>");
		}
	}
	printf("\n");
	return 0;
}









