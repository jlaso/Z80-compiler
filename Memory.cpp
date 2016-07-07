#include <iostream>
#include <fstream>
#include "Memory.h"
#include "general.h"
#include <string>

using namespace std;

Memory::Memory()
{
    size = sizeof(memory);
    for (int i = 0; i < size; ++i) {
        memory[i] = 255;
        //printf("0x%02X ",memory[i]);
    }
}


byte Memory::read(int address)
{
    if (address < size){
        return memory[address];
    }
    return 0;
}

word Memory::readWord(int address)
{
    if (address < size-1){
        return memory[address] | (memory[address+1] << 8);
    }
    return 0;
}

void Memory::write(int address, byte value)
{
    if (address < size){
        memory[address] = value;
    }
}


void Memory::readFromFile(string path, string file)
{
    string fullFile = path+file;
    ifstream fileIn(fullFile, ios::in | ios::binary | ios::ate);

    if(fileIn.fail())
    {
        cout << "File " << file << " couldn't open." << endl;
        exit(-1);
    }
    else
    {
        long fileSize = fileIn.tellg();
        fileIn.seekg(4, ios::beg);   // discard first four bytes,  size and PC
        char* tmp = new char[fileSize];
        fileIn.read(tmp, fileSize);
        for (int i = 0; i < fileSize; ++i) {
            //cout << '0'+tmp[i] << " " ;
            memory[i] = tmp[i];
        }
        delete[] tmp;
    }
    fileIn.close();


}