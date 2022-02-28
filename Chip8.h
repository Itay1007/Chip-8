#ifndef BAROKCHIP_8_CHIP8_H
#define BAROKCHIP_8_CHIP8_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>

using namespace std;

typedef void (*OpcodeEmulator)(void); // function pointer type
typedef std::map<unsigned short, OpcodeEmulator> opcode_emulator_map;

enum CONSTANTS {MEM_SIZE_IN_BYTES=4096,STACK_SIZE_IN_SHORT=16,
    GENERAL_PURPOSE_REGISTERS_NUMBER=16,KEYPAD_IN_BYTES=16};

class Chip8
{
private:
    unsigned char memory[MEM_SIZE_IN_BYTES]; // CHIP-8 memory
    unsigned char keypad[KEYPAD_IN_BYTES];
    unsigned short stack[STACK_SIZE_IN_SHORT];
    unsigned char V[GENERAL_PURPOSE_REGISTERS_NUMBER];
    unsigned short I; // special index register [need only 12 lsb because of the memory size]
    unsigned short pc; // program counter
    unsigned short sp; // stack pointer
    unsigned short delay_timer;
    unsigned short sound_timer;
    unsigned short opcode;
    unsigned short end_program_pc_position; // program counter
public:
    opcode_emulator_map opcode_emulator_mapper;
    Chip8();
    ~Chip8();
    void setup_chip8_memory_fields();
    bool load_chip8_application(const std::string & program_name);
    bool emulate_chip8_application();
    void fetch();
    bool execute();
     void CLS();
     void RET();
     void JP_addr();
     void CALL_addr();
     void SE_Vx_byte();
     void SYS_addr();
     void SNE_Vx_byte();
     void SE_Vx_Vy();
     void LD_Vx_byte();
     void ADD_Vx_byte();
     void LD_Vx_Vy();
     void OR_Vx_Vy();
     void AND_Vx_Vy();
     void XOR_Vx_Vy();
     void ADD_Vx_Vy();
     void SUB_Vx_Vy();
     void SHR();
     void SUBN_Vx_Vy();
     void SHL();
     void SNE_Vx_Vy();
     void LD_I_addr();
     void JP_V0_addr();
     void RND_Vx_byte();
     void DRW_Vx_Vy_nibble();
     void SKP_Vx();
     void SKNP_Vx();
     void LD_Vx_DT();
     void LD_Vx_K();
     void LD_DT_Vx();
     void LD_ST_Vx();
     void ADD_I_Vx();
     void LD_F_Vx();
     void LD_B_Vx();
     void LD_mem_I_Vx();
     void LD_Vx_mem_I();
};

#endif //BAROKCHIP_8_CHIP8_H
