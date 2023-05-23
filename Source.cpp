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
#include <random>


/* 
* 
* dodaj sprawdzanie czy znaki hasla i innych rzeczy podanych przez uzer-ow sa w listach
* 
* na koncu programu pytan uzytkownika o hasle zeby zapisac zmiany
* 
* lub przechowywuje to haslo jako zmienna w klasie uzytkownik
* 
* make prefix t  for timestamp and in decryption-en== to not check those lines since all lines starts with d
typeid(...).name() - type

DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail

*/


int main() {
   

    PasswordPass* ppass = launch();
    ////ppass->showCategories();
    simulateApp(ppass);


    


    /*fmt::print("path to a file is '{}'\n", ppass->getPathToFile());
    fmt::print("\n");
    ppass->showCategories();*/
    
    //encryptFile("secret.txt", "pass");

    //std::string key = "pass";
    //fmt::print(util::white, " This is my message ");



       
    
    return 0;
}
