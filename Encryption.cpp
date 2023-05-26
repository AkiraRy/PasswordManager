#include "Encryption.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

std::string encryptCaeser(const std::string message, const std::string key) {

    std::string encrypted = "";
    const std::string capSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowSet = "abcdefghijklmnopqrstuvwxyz";
    const std::string numSet = "0123456789";
    const std::string symSet = "!@#$%^&*()_+-=[]{}|;:\",<.>/? ";

    for (size_t i = 0; i < message.length(); i++)
    {
        if (isalpha(message[i])) {
            if (islower(message[i])) {

                int shift = int(key[i % key.length()]) % lowSet.length();
                int valueOfCharacter = int(message[i]) - int('a');
                int shiftedValue = (valueOfCharacter + shift);
                encrypted += lowSet[shiftedValue % lowSet.length()];


            }
            else {

                int shift = int(key[i % key.length()]) % capSet.length();
                int valueOfCharacter = int(message[i]) - int('A');
                int shiftedValue = (valueOfCharacter + shift);
                encrypted += capSet[shiftedValue % capSet.length()];

            }
        } else if (isdigit(message[i])) {

            int shift = int(key[i % key.length()]) % numSet.length();
            int valueOfCharacter = numSet.find(message[i]); // start postion of a number in a set

            int shiftedValue = (valueOfCharacter + shift); // shifted NOT fixed postion of a number in a set
         
            encrypted += numSet[shiftedValue % numSet.length()];

        } else {

            int shift = int(key[i % key.length()]) % symSet.length();
            int valueOfCharacter = symSet.find(message[i]); // start postion of a number in a set

            int shiftedValue = (valueOfCharacter + shift); // shifted NOT fixed postion of a number in a set

            encrypted += symSet[shiftedValue % symSet.length()];


            }
    }
    return encrypted;

}

void encryptFile(const std::string filename, const std::string key) {

    auto INstream = std::fstream(filename);

    std::string line;

    std::vector<std::string> encrypted;

    while (getline(INstream, line)) {
        if (line.empty()) {
            continue;
        }
        if (isdigit(line.at(0))) {
            encrypted.push_back(line);
            continue;
        }

        encrypted.push_back(encryptCaeser(line, key));
    }
    INstream.close();


    std::fstream OUTstream = std::fstream(filename);

    if (OUTstream.is_open()) {
        for (auto el : encrypted) {
            OUTstream << el << std::endl;
        }
    }
    OUTstream.close();

}