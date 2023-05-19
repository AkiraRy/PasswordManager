#pragma once
#include <string>

std::string encryptCaeser(const std::string message,const  std::string key);


//std::string encryptXOR(std::string& message, const std::string& key);

void encryptFile(const std::string& filename, const std::string& key);

