#include "Decryption.h"
#include <iostream>
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

    /*std::cout << std::endl;
    std::cout << "DECRYPTION: " << std::endl;*/
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
        decypheredList.push_back(decryptCaeser(line, key));
    }
    INstream.close();
    return decypheredList;
}

/*
        // Create a 

        std::string createPass(bool caps, bool nums, bool symb,int length){
            std::string password  = "";

             std::string combinedSet = lowSet;

             combinedSet += caps ? capSet : "";
             combinedSet += nums ? numSet : "";
             combinedSet += symb ? symSet : "";

            char randChar;

            //use seeded random
            srand (time(NULL));

            //pick random characters from the combined set
            for (int i = 0; i < length; i++){
                randChar = combinedSet[rand() % combinedSet.length() + 1];

                while (randChar == '\0')
                    randChar = combinedSet[rand() % combinedSet.length() + 1];

                password += randChar;
            }

            return password;
         }



    public:

        // generate password based on input param and return
        std::string generateNew(bool capsIn, bool numsIn, bool symbIn, int length){
            std::cout << "\n\nGenerating Password..." << std::endl;
            return createPass(capsIn,numsIn,symbIn,length);
        }

};
*/

/*
// OUTDATED
std::string decrypt(std::string message, std::string key) {
    std::string result = "";

    for (size_t i = 0; i < message.length(); i++)
    {
        int s = int(key[i % key.length()]);
        if (isupper(message[i])) {

            result += char(int(message[i] - s - 65) % 26 + 26 + 65);
        }
        else {
            result += char(int(message[i] - s - 97) % 26 + 26 + 97);
        }
    }
    return result;

}

std::string decryptXOR(std::string & message, const std::string& key) {
    for (int i = 0; i < message.length(); i++) {
        message[i] ^= key[i % key.length()];
    }
    return message;

}
*/

//TODO add 3 parameter to decryptFIle enum type to pick in which mode to decipher
/*
void decryptFile(const std::string& key) {
    
    auto filename = "secret.txt";
    auto stream = std::fstream(
        filename
    );
    std::string line;
    std::vector<std::string> clear;
    std::vector<std::string> encrypted;

    while (stream >> line) {
        encrypted.push_back(line);
    }
    stream.close();

    for (size_t i = 0; i < encrypted.size(); i++)
    {
        clear.push_back(decryptXOR(encrypted.at(i), key));
    }

    std::fstream my_file(filename, std::ios::out);


    for (auto& el : clear) {
        my_file << el << '\n';
    }

    my_file.close();



}
*/
