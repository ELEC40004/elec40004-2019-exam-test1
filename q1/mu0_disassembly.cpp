#include "mu0.hpp"

#include <sstream>
#include <cassert>
#include <iostream>

bool mu0_is_instruction(uint16_t v)
{
    return (v>>12) < 10;
}

string mu0_disassemble_instruction(uint16_t instr)
{
    return "ERR";
}

string mu0_opcode_to_opname(uint16_t opcode)
{
    const vector<string> opnames={
        "LDA", "STA", "ADD", "SUB", "JMP", "JGE", "JNE", "STP", "INP", "OUT"
    };
    return opnames.at(opcode);
}

// Returns true if the given opcode has a memory operand
bool mu0_instruction_has_operand(uint16_t opcode)
{
    assert(opcode < 10);
    return opcode < 7;
}

vector<uint16_t> mu0_read_binary(std::istream &src)
{
    vector<uint16_t> memory;

    int num=1;
    string line;
    while( getline(src, line) ){
        assert(num <= 4096);

        // Trim initial space
        while(line.size()>0 && isspace(line.front())){
            line = line.substr(1); // Remove first characters
        }

        // Trim trailing space
        while(line.size()>0 && isspace(line.back())){
            line.pop_back();
        }

        if(line.size()!=4){
            cerr<<"Line "<<num<<" : expected exactly four chars, got '"<<line<<'"'<<endl;
            exit(1);
        }
        for(int i=0; i<line.size(); i++){
            if(!isxdigit(line[i])){
                cerr<<"Line "<<num<<" : expected only hexadecimal digits, got '"<<line[i]<<'"'<<endl;
                exit(1);
            }
        }

        unsigned x=stoul(line, nullptr, 16);
        assert(x<65536);
        memory.push_back(x);

        num++;
    }
    memory.resize(4096, 0);

    return memory;
}