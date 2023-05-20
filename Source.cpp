#define FMT_HEADER_ONLY
#include <iostream>
#include <string>
#include <vector>
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Utilities.h"
#include <fmt/core.h>
#include <fmt/color.h>


/*
for folder chooser make something with parent dir of this proj, get list of directories ther and take one with secret

DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail

*/
// LXNCGIEPL for pass



int main() {
    PasswordPass*  ppass = launch();
    fmt::print("path to a file is {}\n", ppass->getPathToFile());

    /*fmt::print("OTHERS\n\n");
    for (const auto el : ppass->getOther()) {
        fmt::print("{}\n", el);
    }*/
    
    for (auto& el : ppass->getPasswordList()) {
        std::cout << el.to_string() << std::endl;
    }

    /*fmt::print("PasswordList\n\n");
    for (const auto el : ppass->getPasswordList()) {
        fmt::print("{}\n", el);
    }*/
    


    std::string key = "pass";

    
    
    //encryptFile("secret.txt", key);
    
    /*vector<string> decrypted = decryptFile("secret.txt", key);

    for (auto el : decrypted) {
        vector<string> str = split(el, '|');
        for (auto s : str) {
            fmt::print("Pole {} ", s);
        }
        fmt::print("{} \n", str.size());
    }*/
    
    //vector<string> oneLine = split(decrypted.at(0), '|');
    
    /*int count = 0;
    for (auto el : oneLine) {
        if (count++ == 0) {
            fmt::print("{}\n", el.erase(0,1));
        }
        fmt::print("{}\n", el);
    }*/

    return 0;
}

/*pointers

& - adress of
* - pointer
int *px = &x
* by itslef the value pointed by

if * used after = mean dword go to the pointed address and take the value 

now px points to the value of x


/
*/
// using special characters to mark start/end of kategory 
// name of categories will cyphered with caeser