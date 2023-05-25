#define FMT_HEADER_ONLY
#include <iostream>
#include <string>
#include <vector>
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "Utilities.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <random>



/*
* maybe transfer all sets to namespace
* 
* check if file is empty, than give him prompt again
* 
* fix the inputAnswer to read a string and check if length is 1
* 
* moze zrobutu tak abu wilni misca bylo musorom zapowneni
* 
* w searchPassword zrobuut metodu na wyswitlenna
* * 
look for cin.ignore cin clean
ostatni dostep wypisze uzytkowniku - timestamp
*/


/* 
* dodaj '>' na kazdej linii inputu od uzytkownika
* 
* dodaj sprawdzanie czy znaki hasla i innych rzeczy podanych przez uzer-ow sa w listach
* *   
* make prefix t  for timestamp and in decryption-en to not check those lines since all lines starts with d
typeid(...).name() - type

DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail

*/


int main() {
    



    PasswordPass* ppass = launch();
    simulateApp(ppass);
    
    
    //Last login was 25 day, 22:34:2
    
    return 0;
}
