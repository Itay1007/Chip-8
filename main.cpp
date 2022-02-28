#include <iostream>
#include <string>
#include "Chip8.h"

using namespace std;

bool is_valid_input(int argc, char * argv[]);
bool is_chip8_file(const std::string & program_name);


int main(int argc, char * argv[]) {
    string application_name;
    if (not is_valid_input(argc, argv))
    {
        return 1;
    }

    // valid input to chip8
    application_name = argv[1];

    Chip8 * myChip = new Chip8();

    if(not myChip->load_chip8_application(application_name) || not myChip->emulate_chip8_application())
    {
        return 1;
    }

    myChip->emulate_chip8_application();
    return 0;
}

bool is_valid_input(int argc, char * argv[]) {
    if (argc != 2) {
        cout << argc << " is not a valid number of arguments to the chip8 emulator" << endl;
        cout << "Usage: chip8.exe <chip-8_application_to_emulate.c8>" << endl;
        return false;
    }

    string program_name = argv[1];
    if (not is_chip8_file(program_name)) {
        cout << "Not valid argument to the chip8 emulator: " << program_name << endl;
        cout << "Usage: chip8.exe <chip-8_application_to_emulate.c8>" << endl;
        return false;
    }
    return true;
}

bool is_chip8_file(const string & program_name)
{
    std::size_t found = program_name.find_first_of(".c8");
    if(program_name.substr(found) != ".c8")
    {
        return false;
    }
    return true;
}
