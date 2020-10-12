/*  task1.cpp
 *  Created on 05/09/20 by E. Perkins
 *  opens file: journey.csv
 *      must be latitude, longitude, speed
 *      assumes coordinates are recorded in decimal degrees
 *  ///TODO: find same way to  convert other forms of recording degrees into decimal degrees
 *      Special Characters for example
 *
 *  outputs values to console
 *
 */
#include "Task1.h"

int main(int argc, char* argv[]){
    journey journey;
    openFile(&journey);
    journey.calculateJourney();
    journey.outputJourney();

    return 0;
}

void openFile(journey *trek){
    /*  Asks user for file to analyse (using reqFileName)
     *  checks file can be opened - does not check file extensions
     *  outputs file to vector
     *  separates file by ',' - other delimiters are possible
     *  Assumes csv file is correctly formatted
     *      - no special characters, no alpha
     */
    char delim = ',';
    //ask user for file
    std::string file = reqFileName();
    std::fstream fileInput;


    fileInput.open(file, std::fstream::in); // open file - read only mode
    if (fileInput.is_open()){
        std::cout << "File " << file << " is open \n";
        std::string line;
        int lineCount = 0;
        while (std::getline(fileInput, line)){
        // get each line in turn from supplied file
            if (isdigit(line[0])) {
                // check first character for digit, discard line if not
                ///TODO: More Robust alpha checking
                std::vector<float> reading;
                std::string substring;
                std::stringstream ss(line);

                while (ss.good()){
                    // split string by delimiter
                    std::getline(ss, substring, delim);
                    // convert string to floats - push to reading vector
                    reading.push_back(std::stof(substring));
                }
                if (!trek->inputLatLonSpped(reading)){ // crude error checking
                    std::cout << "Error in data at line " << lineCount << '\n';
                    std::cout << "Line not added \n";
                }
                ++lineCount;
            }
            else{
                ++lineCount;
                continue;
            }

        }
        fileInput.close();
    }
    else{
        std::cout << "file " << file << " is not available \n";
    }

}

std::string reqFileName(void){
    /* asks user for file to analyse
     * returns a string */

    std::string fileName = "journey.csv";
    std::string input = "";
    bool correct = false;

    while (!correct){ // exit loop when user is satisfied with file name
        // inform user of default file name and ask for new one
        std::cout << "Default file name: " << fileName << '\n';
        std::cout << "If this is incorrect, enter new file. Leave blank to use default.\n";

        // get the file name
        std::getline(std::cin, input);
        ///TODO: strip input of leading and trailing white space - could cause issues with file system
        std::cin.clear();

        // check if default is acceptable
        if (input.length() == 0) input = fileName; // if nothing entered, input = default

        std::cout << "file input: " << input << std::endl;
        // check user input with user
        char check[1];

        std::cout << "Is this correct? (Y/N)";
        std::cin.get(*check);
        ///TODO: strip check of leading white space - can cause odd behaviour
        std::cin.clear(); // make sure input is cleared
        std::cin.ignore();
        std::cout << *check << '\n';
        //remSpaces(&check);
        if (char(tolower(*check)) == 'y') correct = true;
        else input = "";
    }
    return input;
}

