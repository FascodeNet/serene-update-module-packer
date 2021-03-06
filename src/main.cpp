#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <initializer_list>
using namespace std; 


int custom_exec_v(std::vector<std::string> args){
    char** argskun=NULL;
    argskun=new char*[args.size() + 2];
    for(size_t i=0;i<args.size();i++){
        argskun[i]=(char*)args[i].c_str();
    }
    argskun[args.size()]=NULL;
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid == 0){
        execvp(argskun[0],argskun);
        perror("exec");
        exit(-1);
    }
    int status;
    pid_t resultkun=waitpid(pid,&status,0);
    if(resultkun < 0){
        perror("waitpid error");
        exit(-1);
    }
    return status;
}

template<class... T> 
int custom_exec(T... args){
	std::vector<std::string> args_vector;
	for(string i : std::initializer_list<string>{args...}){
		args_vector.push_back(i);
	}
	return custom_exec_v(args_vector);
}
char get_random_char(){
    const char CHARS[] = "qwertyuiopasdfghjklzxcvbnm";
    int index=(int)((rand() / ((double)RAND_MAX + 1.0)) * 25);
    char returnkun=CHARS[index];
    return returnkun;
}
int main(int argc,char* argv[]){
    std::vector<std::string> unzip_argskun;
    std::string dir_name(15,'.');
    std::generate_n(dir_name.begin(),15,get_random_char);
    std::string destdir_path="/tmp/" + dir_name + "/";
    unzip_argskun.push_back("unzip");
    unzip_argskun.push_back("-d");
    unzip_argskun.push_back(destdir_path);
    unzip_argskun.push_back(argv[0]);
    custom_exec_v(unzip_argskun);
    chdir(destdir_path.c_str());
    chdir("dist");
    std::string exec_pathkun=destdir_path + "dist/serenelinux-update-wizard";
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid == 0){
        execvp(exec_pathkun.c_str(),argv);
        perror("exec");
        exit(-1);
    }
    int status;
    pid_t resultkun=waitpid(pid,&status,0);
    if(resultkun < 0){
        perror("waitpid error");
        exit(-1);
    }
    custom_exec("rm","-rf",destdir_path.c_str());

    return 0;
}