#include "Decryption.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::string decryptCaeser(const std::string message, const std::string key) {

    std::string decrypted = "";
    const std::string capSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowSet = "abcdefghijklmnopqrstuvwxyz";
    const std::string numSet = "0123456789";
    const std::string symSet = "!@#$%^&*()_+-=[]{}|;:\",<.>/? ";

    int c = 1;
    for (size_t i = 0; i < message.length(); i++)
    {       
        if (isalpha(message[i])) {
            if (islower(message[i])) {
                int shift = int(key[i % key.length()]) % lowSet.length();
                int valueOfCharacter = int(message[i]) - int('a');
                int shiftedValue = (valueOfCharacter - shift);

                if (shiftedValue < 0) {
                    shiftedValue = lowSet.length() + shiftedValue;
                }

                decrypted += lowSet[shiftedValue % lowSet.length()];               
                
            } 
            else {

                int shift = int(key[i % key.length()]) % 26;
                int valueOfCharacter = int(message[i]) - int('A');
                int shiftedValue = (valueOfCharacter - shift);

                if (shiftedValue < 0) {
                    shiftedValue = capSet.length() + shiftedValue;
                }

                decrypted += capSet[shiftedValue % capSet.length()];  
            }
        }
        else if (isdigit(message[i])) {

            int shift = int(key[i % key.length()]) % numSet.length();
            int valueOfCharacter = numSet.find(message[i]); // start postion of a number in a set

            int shiftedValue = (valueOfCharacter - shift); // shifted NOT fixed postion of a number in a set

            if (shiftedValue < 0) {
                shiftedValue = numSet.length() + shiftedValue;
            }

            decrypted += numSet[shiftedValue % numSet.length()];


        } else {

            int shift = int(key[i % key.length()]) % symSet.length();
            int valueOfCharacter = symSet.find(message[i]); // start postion of a number in a set

            int shiftedValue = (valueOfCharacter - shift); // shifted NOT fixed postion of a number in a set

            if (shiftedValue < 0) { // maybe here
                shiftedValue = symSet.length() + shiftedValue;
            }

            decrypted += symSet[shiftedValue % symSet.length()];

            }
    }
    return decrypted;


}

std::vector<std::string> decryptFile(const std::string filename, const std::string key) {
    std::vector<std::string> decypheredList;
    std::string line;
    auto INstream = std::fstream(filename);
    bool isFirstLine = true;

    while (getline(INstream, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;  // Skip the first line
        }
        if (line.empty() ) {
            continue;
        }
        if (isdigit(line.at(0))) {
            decypheredList.push_back(line);
            continue;
        }
        decypheredList.push_back(decryptCaeser(line, key));
    }
    INstream.close();
    return decypheredList;
}