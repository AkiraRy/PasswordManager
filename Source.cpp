#define FMT_HEADER_ONLY
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include <fmt/core.h>
#include <fmt/color.h>



using namespace std;



int main() {


    PasswordPass  ppass = PasswordPass::launch();

    /*string key = "pass";


    std::string message = "DECRYPTED";*/

   //     //PasswordPass pass = PasswordPass::createAccount();

   ////cout << message.find('K') << endl;

   /*string encrypted_message = encryptCaeser(message, key);
   string decrypted_message = decryptCaeser(encrypted_message, key);

   cout << message << endl;
   cout << encrypted_message << endl;
   cout << decrypted_message << endl; */

    


    


    
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