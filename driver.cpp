// written by William Chuter-Davies & Colby Gramelspacher
// barcode number (bcn), license plate (lp), parking status (ps)

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

// process text input from terminal
void process_terminal_input(std::string line, std::map<std::string, std::string>& bcn_to_lp, std::map<std::string, bool>& lp_to_ps) {
    // set all chars in 'line' to lowercase
    std::transform(line.begin(), line.end(), line.begin(), 
        [](unsigned char c) {return std::tolower(c);});
    unsigned int delimeter_pos = line.find_first_of(' ');
    std::string command = line.substr(0, delimeter_pos);
    std::string bcn = line.substr(delimeter_pos);
    // throw on unrecognized barcode number
    if(bcn_to_lp.find(bcn) == bcn_to_lp.end()) {
        throw std::runtime_error("error: unrecognized barcode number");
    }

    // set all chars in 'line' to lowercase
    std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c) {return std::tolower(c);});

    if(command == "park") {
        // set parking status to true
        lp_to_ps[bcn_to_lp[bcn]] = true;
    } else if(command == "unpark") {
        // set parking status to false
        lp_to_ps[bcn_to_lp[bcn]] = false;
    } else if(command == "status") {
        // if parking status is true, return "parked". otherwise, return "unparked"
        if(lp_to_ps[bcn_to_lp[bcn]]) std::cout << "parked\n";
        else std::cout << "unparked\n";
    } else {
        // throw on unrecognized command
        throw std::runtime_error("error: unrecognized command");
    }
    return;
}

// load bcn_to_lp map with reference data
void load_bcn_to_lp(std::map<std::string, std::string>& bcn_to_lp, std::ifstream& ifs) {
    std::string line, bcn, lp;
    std::getline(ifs, line);
    while(std::getline(ifs, line)) {
        unsigned int delimeter_pos = line.find_first_of(',');
        bcn = line.substr(0, delimeter_pos);
        lp = line.substr(delimeter_pos + 1);
        bcn_to_lp[bcn] = lp;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {   
        std::cerr << "usage: ./driver *.csv" << '\n';
        return EXIT_FAILURE;
    }
    std::ifstream ifs(argv[1]);
    if(!ifs) {
        std::cerr << "error: ifs failure" << '\n';
        return EXIT_FAILURE;
    }

    // instantiate barcode number to license plate map
    std::map<std::string, std::string> bcn_to_lp;
    load_bcn_to_lp(bcn_to_lp, ifs);
    // instantiate license plate to parking status map
    std::map<std::string, bool> lp_to_ps;

    std::string command, bcn;
    bool running = true;
    char exit_key;

    while (running){
        std::cout << "\nEnter command and barcode number (ie. park 1234567890).\n";
        std::cin >> command >> bcn;
        process_terminal_input(command, bcn, bcn_to_lp, lp_to_ps);

        std::cout << "\nenter [e] to exit, or any other key to continue.\n";
        std::cin >> exit_key;
        if(exit_key == 'e' || exit_key == 'E'){
            running = false;
            break;
        }
    }

    return EXIT_SUCCESS;
}