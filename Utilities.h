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


namespace util {
	//custom colors
	extern const std::vector<fmt::text_style> colors;
	extern const std::vector<std::string> colorsString;
	extern const fmt::text_style white;
	extern const fmt::text_style error;
	extern fmt::text_style userColor;
	void setUserColor(const fmt::text_style& color);


	//sets for password
	extern const std::string capSet;
	extern const std::string lowSet;
	extern const std::string numSet;
	extern const std::string symSet;

	//eror msg
	extern const std::string wrongOption;
	extern const std::string wrongRange;
	extern const std::string errorPath;
	extern const std::string errorPass;
	extern const std::string pFault;
	extern const std::string Fault;
	extern const std::string cFault;

	//file sys
	extern const std::filesystem::path home;
	extern const std::filesystem::path homeParent;
	extern const std::filesystem::path secretFolder;

	//gui side
	void mainMenu();
	void searchMenu();
	void sortMenu();
	void addPasswordMenu();
	void editPasswordMenu();
	void deletePasswordMenu();
	void addCategoryMenu();
	void deleteCategoryMenu();
	void editingMenu();
}

/**
 * Checks if a string contains banned characters.
 *
 * @param inputString The string to be checked.
 * @return bool Returns true if the string does not contain any banned characters, false otherwise.
 */
bool isNotInSet(const std::string& inputString);


/**
 * Generates a random number within the specified range.
 *
 * @param min The minimum value of the range (inclusive).
 * @param max The maximum value of the range (exclusive).
 * @return int Returns a random number within the specified range.
 */
int random(const int min, int max);

/**
 * Reads a number from the keyboard.
 *
 * @return int Returns the number entered by the user.
 */
int readNumber();

/**
 * Generates a random password with the specified length and options.
 *
 * @param length The length of the generated password.
 * @param includeUppercase Specifies whether to include uppercase letters in the password.
 * @param includeSpecialChars Specifies whether to include special characters in the password.
 * @return std::string Returns the generated random password as a string.
 */
std::string generateRandomPassword(const int length,const  bool includeUppercase, const bool includeSpecialChars);

/**
 * reads an input from user within a given range
 *
 * @param min The minimum value of the range (inclusive).
 * @param max The maximum value of the range (inclusive).
 * @return int Returns the input within a range
 */
int rangeAnswer(int min, int max);


/**
 * Displays a list of files.
 *
 * @param files The vector of strings containing the file names.
 */
void showList(const std::vector<std::string>& files);

/**
 * Retrieves a list of all secret files.
 *
 * @return std::vector<std::string> Returns a vector of strings containing the file names.
 */
std::vector<std::string> allSecrets();


/**
 * Checks if there is a folder with secret files.
 *
 * @return bool Returns true if the secret folder exists, false otherwise.
 */
bool secretFolderIS();

/**
 * Checks if a string contains special characters.
 *
 * @param str The string to be checked.
 * @return bool Returns true if the string contains special characters, false otherwise.
 */
bool containsSpecialCharacters(const std::string& str);

/**
 * Returns the current time in days, hours, minutes, and seconds.
 *
 * @return std::vector<std::string> Returns a vector of strings containing the current time in the format [dd, hh, mm, ss].
 */
std::vector<std::string> time();

/**
 * Writes a timestamp to a file.
 *
 * @param filename The name of the file to write the timestamp to.
 */
void writeTimestamp(const std::string& filename);

/**
 * Splits a string on the provided delimiter.
 *
 * @param s The string to be split.
 * @param delimiter The character to divide the string.
 * @return std::vector<std::string> Returns a vector of strings containing the split substrings.
 */

std::vector<std::string> split(const std::string& s,const char delimiter);


/**
 * Checks if a file was decrypted successfully.
 *
 * @param path The path to the file.
 * @param password The password to the file.
 * @return bool Returns true if the file was decrypted successfully, false otherwise.
 */
bool isDecrypted(const std::string& path, const  std::string& password);

/**
 * Checks if the provided password is correct for the given file.
 *
 * @param path The path to the file.
 * @param errorMessage The message to print out in case of a wrong password.
 * @return std::string Returns the correct password.
 */
std::string correctPassword(const std::string& path);

/**
 * Waits for the correct path to be provided.
 *
 * @param previousPATH The previous path that was entered.
 * @return std::string Returns the correct path to a file.
 */
std::string correctPath(std::string previousPATH);


/**
 * Waits for the correct path to be provided.
 *
 * @param optionOne The first option.
 * @param optionTwo The second option.
 * @param error Specifies if an error occurred.
 * @return char Returns the correct path to a file.
 */
char inputAnswer( const char optionOne, const char optionTwo, bool error);

/**
 * Creates a list of Password objects from the unprepared list of passwords.
 *
 * @param dirt The unprepared list of passwords.
 * @param delimite The delimiter character used to separate password fields.
 * @return std::vector<Password> Returns a clear list of Password objects.
 */
std::vector<Password> passwordList(const std::vector<std::string>& dirt, const  char delimite);


/**
 * Filters the unfiltered vector of strings and returns a filtered vector.
 *
 * @param unfiltered The unfiltered vector of strings.
 * @return std::vector<std::string> Returns the filtered vector of strings.
 */
std::vector<std::string> filter(std::vector<std::string>& unfiltered);