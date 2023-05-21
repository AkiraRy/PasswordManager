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
* make prefix t  for timestamp and in decryption-en== to not check those lines since all lines starts with d
* 
for folder chooser make something with parent dir of this proj, get list of directories ther and take one with secret

typeid(...).name() - type

DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail

*/
// LXNCGIEPL for pass


// i need to create a main function for functioning around and getting prompt from user
/*
i will make a menu like
1 - find passwords
2-..
..
*/
int main() {
    PasswordPass* ppass = launch();
    fmt::print("path to a file is '{}'\n", ppass->getPathToFile());
    fmt::print("\n");
    ppass->showPasswords();
    


    //std::string key = "pass";
    //fmt::print(util::white, " This is my message ");


    //if (presentedIs) {
    //    fmt::print("here\n");
    //    fmt::print("{}", home.append("secret1").string());
    //    /*if (std::filesystem::create_directory(home.string() + "\\secret1")) {
    //        std::cout << "Directory created successfully." << std::endl;
    //    }
    //    else {
    //        std::cout << "Failed to create directory." << std::endl;
    //    }*/
    //}
       
    
    return 0;
}
