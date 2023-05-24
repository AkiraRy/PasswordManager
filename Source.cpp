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
* w searchPassword zrobuut metodu na wyswitlenna
* 
* in these password founds by category add \n at end
* 
look for cin.ignore cin clean
apropo timestamp

ostatni dostep wypisze uzytkowniku 
*/


/* 
* dodaj '>' na kazdej linii inputu od uzytkownika
* 
* dodaj sprawdzanie czy znaki hasla i innych rzeczy podanych przez uzer-ow sa w listach
* 
* variable - haslo
*   
* make prefix t  for timestamp and in decryption-en to not check those lines since all lines starts with d
typeid(...).name() - type

DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail

*/


int main() {

    PasswordPass* ppass = launch();
    simulateApp(ppass);





    
    return 0;
}
