// written by William Chuter-Davies & Colby Gramelspacher
// barcode number (bcn), license plate (lp), parking status (ps)

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

void process_terminal_input(std::string line, std::map<std::string, std::string>& bcn_to_lp, std::map<std::string, bool>& lp_to_ps) {
    std::transform(line.begin(), line.end(), line.begin(), 
        [](unsigned char c) {return std::tolower(c);});
    unsigned int delimeter_pos = line.find_first_of(' ');
    std::string command = line.substr(0, delimeter_pos);
    std::string bcn = line.substr(delimeter_pos + 1);
    
    if(bcn_to_lp.find(bcn) == bcn_to_lp.end()) {
        throw std::runtime_error("unrecognized bcn");
    }
    
    if(command == "park") {
        // set parking status to true
        lp_to_ps[bcn_to_lp[bcn]] = true;
    } else if(command == "unpark") {
        // set parking status to false
        lp_to_ps[bcn_to_lp[bcn]] = false;
    } else if(command == "status") {
        // query parking status
        if(lp_to_ps[bcn_to_lp[bcn]]) {
            std::cout << "  parked" << '\n';
        } 
        else {
            std::cout << "  unparked" << '\n';
        }
    } else {
        // throw on unrecognized command
        throw std::runtime_error("unrecognized command");
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
        std::cerr << "terminating due to program error: ifs failure" << '\n';
        return EXIT_FAILURE;
    }
    
    std::map<std::string, std::string> bcn_to_lp;
    std::map<std::string, bool> lp_to_ps;
    std::string line;
    
    load_bcn_to_lp(bcn_to_lp, ifs);
    
    std::cout << "h - help for summary of available commands" << '\n';
    std::cout << "q - quit" << '\n';
    
    while(true) {
        std::cout << "> ";
        
        std::getline(std::cin, line);
        if(line == "h") {
            std::cout << "usage: [COMMAND] [BCN]" << '\n';
            std::cout  << '\n';
            std::cout << "available commands:" << '\n';
            std::cout << "  park        set parking status to true" << '\n';
            std::cout << "  unpark      set parking status to false" << '\n';
            std::cout << "  status      query parking status" << '\n';
        } else if(line == "q") {
            return EXIT_SUCCESS;
        } else {
            try {
                process_terminal_input(line, bcn_to_lp, lp_to_ps);
            }
            catch(const std::exception& e) {
                std::cerr << "program error: " << e.what() << '\n';
            }
        }
    }
    
    std::cerr << "terminating due to program error: unexpected path" << '\n';
    return EXIT_FAILURE;
}