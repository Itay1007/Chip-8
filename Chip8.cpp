#include <string>
#include <map>
#include "Chip8.h"
#include <fstream>
#include <windows.h>

Chip8::Chip8()
{
    setup_chip8_memory_fields();
}

Chip8::~Chip8()
{

}

//void Chip8::setup_opcodes_emulators()
//{
//    opcode_emulator_mapper.insert({0x00E0, &Chip8::CLS});
//    opcode_emulator_mapper.insert({0x00EE, &Chip8::RET});
//    opcode_emulator_mapper.insert({0x0000, &Chip8::SYS_addr});
//    opcode_emulator_mapper.insert({0x1000, &Chip8::JP_addr});
//    opcode_emulator_mapper.insert({0x2000, &Chip8::CALL_addr});
//    opcode_emulator_mapper.insert({0x3000, &Chip8::SE_Vx_byte});
//    opcode_emulator_mapper.insert({0x4000, &Chip8::SNE_Vx_byte});
//    opcode_emulator_mapper.insert({0x5000, &Chip8::SE_Vx_Vy});
//    opcode_emulator_mapper.insert({0x6000, &Chip8::LD_Vx_byte});
//    opcode_emulator_mapper.insert({0x7000, &Chip8::ADD_Vx_byte});
//    opcode_emulator_mapper.insert({0x8000, &Chip8::LD_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8001, &Chip8::OR_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8002, &Chip8::AND_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8003, &Chip8::XOR_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8004, &Chip8::ADD_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8005, &Chip8::SUB_Vx_Vy});
//    opcode_emulator_mapper.insert({0x8006, &Chip8::SHR});
//    opcode_emulator_mapper.insert({0x8007, &Chip8::SUBN_Vx_Vy});
//    opcode_emulator_mapper.insert({0x800E, &Chip8::SHL});
//    opcode_emulator_mapper.insert({0x9000, &Chip8::SNE_Vx_Vy});
//    opcode_emulator_mapper.insert({0xA000, &Chip8::LD_I_addr});
//    opcode_emulator_mapper.insert({0xB000, &Chip8::JP_V0_addr});
//    opcode_emulator_mapper.insert({0xC000, &Chip8::RND_Vx_byte});
//    opcode_emulator_mapper.insert({0xD000, &Chip8::DRW_Vx_Vy_nibble});
//    opcode_emulator_mapper.insert({0xE09E, &Chip8::SKP_Vx});
//    opcode_emulator_mapper.insert({0xE0A1, &Chip8::SKNP_Vx});
//    opcode_emulator_mapper.insert({0xF007, &Chip8::LD_Vx_DT});
//    opcode_emulator_mapper.insert({0xF00A, &Chip8::LD_Vx_K});
//    opcode_emulator_mapper.insert({0xF015, &Chip8::LD_DT_Vx});
//    opcode_emulator_mapper.insert({0xF018, &Chip8::LD_ST_Vx});
//    opcode_emulator_mapper.insert({0xF01E, &Chip8::ADD_I_Vx});
//    opcode_emulator_mapper.insert({0xF029, &Chip8::LD_F_Vx});
//    opcode_emulator_mapper.insert({0xF033, &Chip8::LD_B_Vx});
//    opcode_emulator_mapper.insert({0xF055, &Chip8::LD_mem_I_Vx});
//    opcode_emulator_mapper.insert({0xF065, &Chip8::LD_Vx_mem_I});
//}




bool Chip8::load_chip8_application(const std::string & application_name)
{
    // max_application_size: MEMORY_SIZE - APPLICATION_START_POSITION
    char full_application_path[MAX_PATH];

    GetFullPathName(application_name.c_str(), MAX_PATH, full_application_path, nullptr);


    std::ifstream application_file(full_application_path , std::ios::binary);

    std::vector<unsigned char> applications_row_data_in_bytes(std::istreambuf_iterator<char>(application_file), {});
    cout << "[+] Loading to memory: " << full_application_path << endl;

    if(applications_row_data_in_bytes.size() >= MEM_SIZE_IN_BYTES - 0x200)
    {
        cout << "[-] Can not loading to memory. " << endl;
        cout << "[-] File size too big for memory: " << applications_row_data_in_bytes.size() << endl;
        return false;
    }
    for(int i = 0; i < applications_row_data_in_bytes.size(); i++)
    {
        printf("0x %x\n", (char) applications_row_data_in_bytes[i]);
        memory[i + 0x200] = (char) applications_row_data_in_bytes[i];
    }
    end_program_pc_position = applications_row_data_in_bytes.size() + 0x200;

    application_file.close();
    return true;
}

//
//bool Chip8::load_chip8_application(const std::string & application_name)
//{
//    char full_application_path[MAX_PATH];
//    GetFullPathName(application_name.c_str(), MAX_PATH, full_application_path, nullptr);
//    printf("Loading: %s\n", full_application_path);
//
//    // Open file
//    FILE * pFile = fopen(full_application_path, "rb");
//    if (pFile == NULL)
//    {
//        fputs ("File error", stderr);
//        return false;
//    }
//
//    // Check file size
//    fseek(pFile , 0 , SEEK_END);
//    long lSize = ftell(pFile);
//    rewind(pFile);
//    printf("Filesize: %d\n", (int)lSize);
//
//    // Allocate memory to contain the whole file
//    char * buffer = (char*)malloc(sizeof(char) * lSize);
//    if (buffer == NULL)
//    {
//        fputs ("Memory error", stderr);
//        return false;
//    }
//
//    // Copy the file into the buffer
//    size_t result = fread (buffer, 1, lSize, pFile);
//    if (result != lSize)
//    {
//        fputs("Reading error",stderr);
//        return false;
//    }
//
//    // Copy buffer to Chip8 memory
//    if((4096-512) > lSize)
//    {
//        for(int i = 0; i < lSize; ++i)
//        {
//            printf("0x %x\n", buffer[i]);
//            memory[i + 512] = buffer[i];
//        }
//
//    }
//    else
//        printf("Error: ROM too big for memory");
//
//    // Close file, free buffer
//    fclose(pFile);
//    free(buffer);
//
//    return true;
//}





void Chip8::fetch()
{
    // fetch
    opcode = memory[pc] << 8 | memory[pc + 1];
}

bool Chip8::execute()
{
    try {
        // decode
        switch(opcode & 0xF000)
        {
            case 0x0000:
                switch(opcode & 0x00FF)
                {
                    case 0x0000:
                        SYS_addr();
                        break;
                    case 0x00E0:
                        CLS();
                        break;
                    case 0x00EE:
                        RET();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            case 0x1000:
                JP_addr();
                break;
            case 0x2000:
                CALL_addr();
                break;
            case 0x3000:
                SE_Vx_byte();
                break;
            case 0x4000:
                SNE_Vx_byte();
                break;
            case 0x5000:
                switch(opcode & 0x000F)
                {
                    case 0:
                        SE_Vx_Vy();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            case 0x6000:
                LD_Vx_byte();
                break;
            case 0x7000:
                ADD_Vx_byte();
                break;
            case 0x8000:
                switch(opcode & 0x000F)
                {
                    case 0:
                        LD_Vx_Vy();
                        break;
                    case 1:
                        OR_Vx_Vy();
                        break;
                    case 2:
                        AND_Vx_Vy();
                        break;
                    case 3:
                        XOR_Vx_Vy();
                        break;
                    case 4:
                        ADD_Vx_Vy();
                        break;
                    case 5:
                        SUB_Vx_Vy();
                        break;
                    case 6:
                        SHR();
                        break;
                    case 7:
                        SUBN_Vx_Vy();
                        break;
                    case 0xE:
                        SHL();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            case 0x9000:
                switch(opcode &0x000F)
                {
                    case 0:
                        SNE_Vx_Vy();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            case 0xA000:
                LD_I_addr();
                break;
            case 0xB000:
                JP_V0_addr();
                break;
            case 0xC000:
                RND_Vx_byte();
                break;
            case 0xD000:
                DRW_Vx_Vy_nibble();
                break;
            case 0xE000:
                switch(opcode & 0x00FF)
                {
                    case 0x9E:
                        SKP_Vx();
                        break;
                    case 0xA1:
                        SKNP_Vx();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            case 0xF000:
                switch(opcode & 0x00FF) {
                    case 0x0007:
                        LD_Vx_DT();
                        break;
                    case 0x000A:
                        LD_Vx_K();
                        break;
                    case 0x0015:
                        LD_DT_Vx();
                        break;
                    case 0x0018:
                        LD_ST_Vx();
                        break;
                    case 0x001E:
                        ADD_I_Vx();
                        break;
                    case 0x0029:
                        LD_F_Vx();
                        break;
                    case 0x0033:
                        LD_B_Vx();
                        break;
                    case 0x0055:
                        LD_mem_I_Vx();
                        break;
                    case 0x0065:
                        LD_Vx_mem_I();
                        break;
                    default:
                        printf("[-] 0x%x is invalid opcode!", opcode);
                        return false;
                }
            default:
                printf("[-] 0x%x is invalid opcode!", opcode);
                return false;
        }

        if(sound_timer > 0)
        {
            cout << "\a" << endl;
            sound_timer--;
        }

        if(delay_timer > 0)
        {
            delay_timer--;
        }
        return true;
    }
    catch(exception e)
    {
        cout << opcode << endl;
    }


    return true;
}

bool Chip8::emulate_chip8_application()
{
    int count = 0;
    while(pc < end_program_pc_position)
    {
        fetch();
        if(not execute())
        {
            return false;
        }
        if(count % 10000)
        {
            cout << count << endl;
        }

        count++;
    }
    return true;
}

void Chip8::setup_chip8_memory_fields()
{
    // clear the current opcode
    opcode = 0;

    // clear the registers
    for(int i = 0; i <= 0xF; i++)
    {
        V[i] = 0;
    }
    I = delay_timer = sound_timer = sp = 0;
    pc =  0x200;

    // clear the stack
    for(int i = 0; i < STACK_SIZE_IN_SHORT; i++)
    {
        stack[i] = 0;
    }

    // clear the memory
    for(int i = 0; i < MEM_SIZE_IN_BYTES; i++)
    {
        memory[i] = 0;
    }
}

// 00E0 - CLS
// Clear the screen.
void Chip8::CLS()
{
    pc += 2;
}

// 00EE - RET
// Return from a subroutine.
// The chip-8 interpreter sets the program counter to the address at the top of the stack,
// then subtracts 1 from the stack pointer.
void Chip8::RET()
{
    pc = stack[sp];
    sp--;
}


// 1nnn - JP addr
// Jump to location nnn.
// The interpreter sets the program counter to nnn.
void Chip8::JP_addr()
{
    unsigned short jmp_addr = opcode & 0x0FFF;
    pc = jmp_addr;
}

// 2nnn - CALL addr
// Call subroutine at nnn.
// The interpreter increments the stack pointer,
// then puts the current PC + 2 which is the next instruction on the top of the stack.
// The PC is then set to nnn.
void Chip8::CALL_addr()
{
    sp++;
    stack[sp] = pc + 2;
    unsigned short jmp_addr = opcode & 0x0FFF;
    pc = jmp_addr;
}

// 3xkk - SE Vx, byte
// Skip next instruction if Vx = kk.
// The interpreter compares register Vx to kk,
// and if they are equal,
// increments the program counter by 2.
void Chip8::SE_Vx_byte()
{
    unsigned char reg_idx = (0x0F00 & opcode) >> 8;
    if(V[reg_idx] == (opcode & 0x00FF))
    {
        pc += 4;
    }
    else
    {
        pc += 2;
    }
}

// 4xkk - SNE Vx, byte
// Skip next instruction if Vx != kk.
// The interpreter compares register Vx to kk,
// and if they are not equal,
// increments the program counter by 2.
void Chip8::SNE_Vx_byte()
{
    unsigned char reg_idx = (0x0F00 & opcode) >> 8;
    if(V[reg_idx] != (opcode & 0x00FF))
    {
        pc += 4;
    }
    else
    {
        pc += 2;
    }
}

// 5xy0 - SE Vx, Vy
// Skip next instruction if Vx = Vy.
// The interpreter compares register Vx to register Vy,
// and if they are equal,
// increments the program counter by 2.
void Chip8::SE_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    if(V[x] == V[y])
    {
        pc += 4;
    }
    else
    {
        pc += 2;
    }
}

// 6xkk - LD Vx, byte
// Set Vx = kk.
// The interpreter puts the value kk into register Vx.
void Chip8::LD_Vx_byte()
{
    unsigned char reg_idx = (0x0F00 & opcode) >> 8;
    V[reg_idx] = (opcode & 0x00FF);
    pc += 2;
}

// 7xkk - ADD Vx, byte
// Set Vx = Vx + kk.
// Adds the value kk to the value of register Vx,
// then stores the result in Vx.
void Chip8::ADD_Vx_byte()
{
    unsigned char reg_idx = (0x0F00 & opcode) >> 8;
    V[reg_idx] += (opcode & 0x00FF);
    pc += 2;
}

// 8xy0 - LD Vx, Vy
// Set Vx = Vy.
// Stores the value of register Vy in register Vx.
void Chip8::LD_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    V[x] = V[y];
    pc += 2;
}

// 8xy1 - OR Vx, Vy
// Set Vx = Vx OR Vy.
// Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
void Chip8::OR_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    V[x] = V[x] | V[y];
    pc += 2;
}

// 8xy2 - AND Vx, Vy
// Set Vx = Vx AND Vy.
// Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
void Chip8::AND_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    V[x] = V[x] & V[y];
    pc += 2;
}

// 8xy3 - XOR Vx, Vy
// Set Vx = Vx XOR Vy.
// Performs a bitwise exclusive OR on the values of Vx and Vy,
// then stores the result in Vx.
// An exclusive OR compares the corrseponding bits from two values,
// and if the bits are not both the same,
// then the corresponding bit in the result is set to 1.
// Otherwise, it is 0.
void Chip8::XOR_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    V[x] = V[x] ^ V[y];
    pc += 2;
}

// 8xy4 - ADD Vx, Vy
// Set Vx = Vx + Vy, set VF = carry.
// The values of Vx and Vy are added together.
// If the result is greater than 8 bits (i.e., > 255,) VF is set to 1,
// otherwise 0.
// Only the lowest 8 bits of the result are kept,
// and stored in Vx.
void Chip8::ADD_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;

    if( (unsigned short) V[x] + (unsigned short) V[y] > 0xFF)
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[x] = V[x] + V[y];
    pc += 2;
}

// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx >= Vy, then VF is set to 1, otherwise 0.
// Then Vy is subtracted from Vx, and the results stored in Vx.
void Chip8::SUB_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;

    if(V[x] >= V[y])
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[x] = V[x] - V[y];
    pc += 2;
}

// 8xy6 - SHR Vx {, Vy}
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0
// Then Vx is divided by 2
// Set Vx = Vx SHR 1
void Chip8::SHR() {
    unsigned char x = (0x0F00 & opcode) >> 8;
    V[0xF] = V[x] & 1;
    V[x] = V[x] >> 1;
    pc += 2;
}

// 8xy7 - SUBN Vx, Vy
// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy >= Vx, then VF is set to 1, otherwise 0.
// Then Vx is subtracted from Vy, and the results stored in Vx.
void Chip8::SUBN_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;

    if(V[y] >= V[x])
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[x] = V[y] - V[x];
    pc += 2;
}

// 8xyE - SHL Vx {, Vy}
// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0.
// Then Vx is multiplied by 2.
void Chip8::SHL()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    V[0xF] = (V[x]) >> 7;
    V[x] = V[x] << 1;
    pc += 2;
}

// 9xy0 - SNE Vx, Vy
// Skip next instruction if Vx != Vy.
//
// The values of Vx and Vy are compared, and if they are not equal,
// the program counter is increased by 2.
void Chip8::SNE_Vx_Vy()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char y = (0x00F0 & opcode) >> 4;
    if(V[x] != V[y])
    {
        pc += 4;
    }
    else
    {
        pc += 2;
    }
}

// Annn - LD I, addr
// Set I = nnn.
// The value of register I is set to nnn.
void Chip8::LD_I_addr()
{
    I = 0x0FFF & opcode;
    pc += 2;
}

// Bnnn - JP V0, addr
// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void Chip8::JP_V0_addr()
{
    unsigned short jmp_addr = opcode & 0x0FFF;
    pc = jmp_addr + V[0];
}

// Cxkk - RND Vx, byte
// Set Vx = random byte AND kk.
// The interpreter generates a random number from 0 to 255,
// which is then ANDed with the value kk.
// The results are stored in Vx.
void Chip8::RND_Vx_byte()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char random_number = rand() % 0xFF;
    V[x] = random_number & (0x00FF & opcode);
    pc += 2;
}

// Dxyn - DRW Vx, Vy, nibble
// Display n-byte sprite starting at memory location I at (Vx, Vy),
// set VF = collision.
// The interpreter reads n bytes from memory,
// starting at the address stored in I.
// These bytes are then displayed as sprites on screen at coordinates (Vx, Vy).
// Sprites are XORed onto the existing screen.
// If this causes any pixels to be erased, VF is set to 1,
// otherwise it is set to 0.
// If the sprite is positioned so part of it is outside the coordinates of the display,
// it wraps around to the opposite side of the screen.
void Chip8::DRW_Vx_Vy_nibble()
{
    pc += 2;
}

// Ex9E - SKP Vx
// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard,
// and if the key corresponding to the value of Vx is currently in the down position,
// PC is increased by 2.
void Chip8::SKP_Vx()
{
    pc += 2;
}

// ExA1 - SKNP Vx
// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard,
// and if the key corresponding to the value of Vx is currently
// in the up position,
// PC is increased by 2.
void Chip8::SKNP_Vx()
{
    pc += 2;
}

// Fx07 - LD Vx, DT
// Set Vx = delay timer value.
// The value of DT is placed into Vx.
void Chip8::LD_Vx_DT()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    V[x] = delay_timer;
    pc += 2;
}

// Fx0A - LD Vx, K
// Wait for a key press, store the value of the key in Vx.
// All execution stops until a key is pressed,
// then the value of that key is stored in Vx.
void Chip8::LD_Vx_K()
{
    pc += 2;
}

// Fx15 - LD DT, Vx
// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void Chip8::LD_DT_Vx()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    delay_timer = V[x];
    pc += 2;
}

// Fx18 - LD ST, Vx
// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void Chip8::LD_ST_Vx()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    sound_timer = V[x];
    pc += 2;
}

// Fx1E - ADD I, Vx
// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
void Chip8::ADD_I_Vx()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    I = I + V[x];
    pc += 2;
}

// Fx29 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding
// to the value of Vx.
void Chip8::LD_F_Vx()
{
    pc += 2;
}

// Fx33 - LD B, Vx
// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// The interpreter takes the decimal value of Vx,
// and places the hundreds digit in memory at location in I,
// the tens digit at location I+1, and the ones digit at location I+2.
void Chip8::LD_B_Vx()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    unsigned char temp = V[x];
    memory[I + 2] = temp % 10;
    temp /= 10;
    memory[I + 1] = temp % 10;
    temp /= 10;
    memory[I] = temp % 10;
    pc += 2;
}

// Fx55 - LD [I], Vx
// The interpreter copies the values of registers V0 through Vx into memory,
// starting at the address in I.
void Chip8::LD_mem_I_Vx()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    for(int i = 0; i < x; i++)
    {
        memory[I + 0] = V[i];
    }
    pc += 2;
}

// Fx65 - LD Vx, [I]
// The interpreter reads values from memory starting at location I
// into registers V0 through Vx.
void Chip8::LD_Vx_mem_I()
{
    unsigned char x = (0x0F00 & opcode) >> 8;
    for(int i = 0; i < x; i++)
    {
        V[i] = memory[I + 0];
    }
    pc += 2;
}

// Fx55 - LD [I], Vx
// The interpreter copies the values of registers V0 through Vx into memory,
// starting at the address in I.
void Chip8::SYS_addr()
{
    unsigned short jmp_addr = opcode & 0x0FFF;
    pc = jmp_addr;
}
