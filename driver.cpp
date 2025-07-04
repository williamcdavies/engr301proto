//Authors: William Chuter-Davies, Colby Gramelspacher
#include <iostream>
#include <algorithm>


//Will parse commands. Return false if command is unrecognized
bool ParseCommand(const std::string command) {
    //Converts all string characters to lowercase
    std::string temp = command;
    std::transform(temp.begin(), temp.end(), temp.begin(), std::tolower);

    if (temp == "add") {
        //Check and add VIN to list
        return true;
    }
    else if (temp == "remove") {
        //Check and remove VIN from list
        return true;
    }
    else if (temp == "legal") {
        //Check if parked legally or illegally
        return true;
    }
    return false;
}

int main()
{
    std::string command = "remove";
    if (!ParseCommand(command)) std::cout << "Error: Unrecognized Command!\n";
    return 0;
}
