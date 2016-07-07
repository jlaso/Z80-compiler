#ifndef MEMORY_H
#define MEMORY_H

#include "general.h"
#include <string>

using namespace std;

class Memory
{
private:
    byte memory[65536];
    int size;

public:
    Memory();
    byte read(int address);
    void write(int address, byte value);
    void readFromFile(string path, string file);
    word readWord(int address);

};

#endif // MEMORY_H
