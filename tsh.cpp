#include <tsh.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
    std::stringstream stream; //for parsing
    stream.str(cmd); //get content from cmd
    char tempChar; //for storing each char
    string tempString = ""; //storing char values to put into cmdtokens
    int tokensPosition = 0; //for filling in tokens (start at 0)

    //while cmd still being parsed
    while (stream.get(tempChar)) {
        if (tempChar != ' ' && tempChar != '\n') {
            tempString += tempChar;
            if(stream.peek() == EOF){
                char* tempString2 = new char[tempString.length()];
                strcpy(tempString2, tempString.c_str());
                cmdTokens[tokensPosition] = tempString2;
                tokensPosition++;
                tempString = "";
                break;
            }
        }
        else {
            char* tempString2 = new char[tempString.length()];
            strcpy(tempString2, tempString.c_str());
            cmdTokens[tokensPosition]= tempString2;
            tokensPosition++;
            tempString = "";
        }
    }
}

//parent waits, child executes
void simple_shell::exec_command(char** argv) {
    if (int pid = fork() == 0) {
      if(argv[1]){
	execvp(argv[0], argv);
      }
      else{
	execvp(argv[0], &argv[0]);
      }
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
}

//check if cmd is equal to quit
bool simple_shell::isQuit(char* cmd) {
  return strcmp("quit", cmd) == 0;
}
