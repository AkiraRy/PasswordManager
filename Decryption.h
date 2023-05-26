#pragma once
#include <string>
#include <vector>

/// \brief Decrypts a message with the Vigenere cipher using a key.
///
/// \param message The message to be decrypted.
/// \param key The key used for decryption.
/// \return The decrypted message.
std::string decryptCaeser(const std::string message, const std::string key);


/// \brief Decrypts a file with the Vigenere cipher using a key.
///
/// \param filename The name of the file to be decrypted.
/// \param key The key used for decryption.
/// \return A vector of strings containing the decrypted lines of the file.
std::vector<std::string> decryptFile(const std::string filename, const std::string key);