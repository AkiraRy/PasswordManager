#pragma once
#include <string>

std::string decryptCaeser(const std::string message, const std::string key);

//std::string decryptXOR(std::string& message, const std::string& key);

void decryptFile(const std::string& key);




