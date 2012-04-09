#ifndef dir_tools_h
#define dir_tools_h

#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <vector>
#include <unistd.h>

using namespace std;

/**
 *  Fun��es usadas para acessar diret�rios
 */
string getCurrentDirectory();
vector<string> travelDirectory(string directory);
void travelDirectoryRecursive(string directory, vector<string> *fullList);


#endif
