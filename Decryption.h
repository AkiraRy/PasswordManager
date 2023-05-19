#pragma once
#include <string>
#include <vector>

std::string decryptCaeser(const std::string message, const std::string key);

//std::string decryptXOR(std::string& message, const std::string& key);

std::vector<std::string> decryptFile(const std::string filename, const std::string key);




