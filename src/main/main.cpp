#include "main.hpp"

int main(int argc, char* argv[]) {
    // the program has one mandatory argument and it is
    // the psedopotential file in UPF format
    // the output will be written to automatically generated
    // output file

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return(RV_Global::NO_INPUT_FILE);
    }

    DBG::debug_level = 2;

    IFParser parser(argv[1]);

    return(RV_Global::ALL_OK);
}