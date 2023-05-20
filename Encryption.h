#pragma once
#include <string>

/// \brief Encrypts a message with the Vigenere cipher using a key.
///
/// \param message The message to be encrypted.
/// \param key The key used for encryption.
/// \return The encrypted message.
std::string encryptCaeser(const std::string message,const  std::string key);


//std::string encryptXOR(std::string& message, const std::string& key);

/// \brief Encrypts a file with the Vigenere cipher using a key.
///
/// \param filename The name of the file to be encrypted.
/// \param key The key used for decryption.
/// \return Nothing, just encrypts the file itself.
void encryptFile(const std::string filename, const std::string key);

