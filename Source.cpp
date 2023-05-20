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

add maybe namespace for already undentivible colors or so idk XD maybe like for errors
typeid(...).name() - type
when login by folder not path, check if folder is there (secret in 1 parent folder) if not say it to a user, and then he can choose to create, go by path or leave

add maybe namespace for using eror message to not redefine them everywhere.

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
    /*PasswordPass* ppass = launch();
    fmt::print("path to a file is {}\n", ppass->getPathToFile());
    fmt::print("\n");
    ppass->showPasswords();
    fmt::print("after");


    std::string key = "pass";*/

    //MODUL FOR CREATIN AN FOLDER IF DOESNT EXISTS
    auto home = std::filesystem::current_path();
    home = home.parent_path();
    std::cout << home << std::endl;
    auto dir_it = std::filesystem::directory_iterator(home);
    bool presentedIs = true;
    for (auto element : dir_it) {
        if (element.path().filename() == "secret") {
            fmt::print("good");
            presentedIs = false;
        }

        std::cout << element.path().filename() << "\n";
    }

    if (presentedIs) {
        fmt::print("here\n");
        fmt::print("{}", home.append("secret1").string());
        /*if (std::filesystem::create_directory(home.string() + "\\secret1")) {
            std::cout << "Directory created successfully." << std::endl;
        }
        else {
            std::cout << "Failed to create directory." << std::endl;
        }*/
    }
       
    
    return 0;
}
