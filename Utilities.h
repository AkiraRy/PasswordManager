#pragma once
#include <regex>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>
#include "Password.h"

/// \brief Checks if a string has special Characters 
///
/// \param str - message
/// \returns bool
bool containsSpecialCharacters(const std::string& str);

/// \brief current time
///
/// \returns hh mm ss current time in vector
std::vector<int> time();

void wrtieTimestamp(const std::string filename);

/// \brief Splits a string on provided delimiter
///
/// \param s - message
/// \param delimiter - character to divide string  
/// \returns splited vector<string> 
std::vector<std::string> split(const std::string& s,const char delimiter);

/// \brief Checks if file was decrypted successfully
///
/// \param path - path to a file
/// \param passsword - password to a file
/// \returns bool
bool isDecrypted(const std::string path, const  std::string password);

/// \brief Checks if provided password is correct for given file
///
/// \param path - path to a file
/// \param errorMessage - message to printout in case of wrong password
/// \returns correct password	
std::string correctPassword(const std::string path, const  std::string errorMessage);

/// \brief Waits for correctPath to be provided
///
/// \param errorMessage - message to printout in case of wrong password
/// \returns correct path to a file
std::string correctPath(const std::string errorMessage);

/// \brief Waits for correctPath to be provided
///
/// \param errorMessage - message to printout in case of wrong password
/// \returns correct path to a file
char inputAnswer(const std::string errorMessage, const char optionOne, const char optionTwo);

/// \brief Makes an list type of Password
///
/// \param dirt - unprepared list of passwords
/// \returns clear list of Passwords
std::vector<Password> passwordList(const std::vector<std::string> dirt, const  char delimite);
