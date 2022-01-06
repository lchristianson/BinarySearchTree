#ifndef _PG4_
#define _PG4_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv);
bool ProcessCommand();
void Print();
void RPrint();
void AddCommand(string cmd);
void RemoveCommand(string cmd);
void LookupCommand(string cmd);
void EditCommand(string cmd);
#endif