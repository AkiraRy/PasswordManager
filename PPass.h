#pragma once
#include <string>
#include <vector>
#include <map>
#include "Password.h"


enum class SearchOption {
    ByName,
    ByCategory,
    ByLogin,
    ByWebSite,
};

/// \class PasswordPass
/// \brief Object with decrypted passwords
class PasswordPass {
private:
    //fmt::text_style USER_SPECIFIED_COLOR = util::white;

    std::vector<Password> passwordList;

    std::vector<std::string> other;

    std::string password;

    std::string pathToFile;

    std::vector<int> timestamp;

    std::map<std::string, std::vector<Password>> passwordMap; // New map, category - passwords listt

private:
    /// \brief Private constructor to initialize the password list.
    /// \param path to a file, and master password
    PasswordPass(const std::string pathToFile,const std::string password);

    /*
    * @brief Login with path to PPass
    *
    * @param string - path if logged from Folder
    *
    * @return PasswordPass pointer
    */
    static PasswordPass* loginWithPath(const std::string autoPath, const std::string& autoPass);

    /// \brief Login by choosing file from a folder.
    static PasswordPass* loginFromFolder();


public:
    void deletePasswordFromList(std::vector<std::string> fieldsOfDeletedVector);

    /**
    * @brief Sets additional string data.
    * @param vec The vector of strings.
    */
    void setOther(const std::vector<std::string> vec) {
        other = vec;
    }
    /**
    * @brief Displays the file path.
    */
    void showPATH();

    /*
    *  @brief saves changes made during program
    */
    void saveChanges();

    /**
    * @brief Deletes password withina certain category
    */
    void deletePasswordsByCategory(const std::string& category);

    /**
    * Checks if input category is presented in class PasswordPass
    *
    * @return std::string Returns category that is included in PasswordPass.
    */
    std::string presentCategory();

    /**
    * Checks if input category is not in class PasswordPass
    *
    * @return std::string Returns category that is not included in PasswordPass.
    */
    std::string uniqueCategory();
    
    /*
    * Show statistics about password, Popularity, safeity and if it was used
    * 
    * @params string to check
    */
    void passwordStatistics(const std::string password);

    /*
    * @brief Checks if password was used before
    */
    bool usedBefore(const std::string password);

    /*
    * @brief Deletes password from list
    */
    void deletePassword();

    /*
    * @brief edits choosen password
    */
    void editPassword();

    /*
    * @brief deletes whole category with passwords inside
    */
    void deleteCategory();

    /*
    * @brief add`s new category to catalogue
    */
    void addCategory();

    /*
    * @brief adds password to list
    */
    void addPassword();

    /*
    * @brief Uses helpSort() for every case with parameters
    */
    void sortPasswords();

    /*
    * @brief Sorts passwords on given type(s)
    *
    * @param vector<string> on which field to sort
    */
    void helpSort(const std::vector<std::string> sortFields);

    /*
    * @brief gets all password within a category
    * 
    * @return A vector of Password
    */    
    std::vector<Password> getPasswordsByCategory(const std::string& category);

    /*
    * @brief getter for PasswordMap
    * 
    * @return map<string, vector<Password>>
    */
    const std::map<std::string, std::vector<Password>>& getPasswordMap() const {
        return passwordMap;
    }

    /*
    * @brief searches password on given condition and then printouts it 
    */
    void searchPassword();

    /*
    * @brief Function to populate the passwordMap based on passwordList categories
    */
    void populatePasswordMap();

    /*
    * @brief Function to retrieve all categories available
    * 
    * @return Vector of strings
    */
    std::vector<std::string> getAllCategories() const;

    /*
    * @brief Function show all categories available
    */
    void showCategories();


    /// \brief Creates a new password manager account.
    /// \sa loginIntoAccount(), launch()
    static PasswordPass* createAccount();

    /// \brief Logs into an existing password manager account.
    /// \return The PasswordPass object representing the logged-in account.
    /// \sa createAccount(), launch()
    static PasswordPass* loginIntoAccount();

    /*
    * @brief Setter for PasswordList
    */
    void setPasswordList(const std::vector<Password>& list) { passwordList = list; }

    /*
    * @brief Getter for PasswordList
    */
    const std::vector<Password>& getPasswordList() const {
        return passwordList;
    }

    /*
    * @brief Shows info inside vector other
    */
    void showOther();

    /*
    * @brief Getter for vector other
    */
    const std::vector<std::string>& getOther() const {
        return other;
    }

    /*
    * @brief Getter of file path
    */
    const std::string& getPathToFile() const {
        return pathToFile;
    }

    /*
    * @brief Getter of master password
    */
    const std::string& getPassword() const {
        return password;
    }

    /*
    * @brief Shows master password
    */
    void showPasswords();


    ~PasswordPass();
};

/*
* @brief Template for password creation consisting of {name, website, login}
* 
* @return vector<string> of fields
*/
std::vector<std::string> templatePassword();

/*
* @brief Main logic of PasswordApp aka CORE
*
*/
void simulateApp(PasswordPass*& ppass);

/*
* @brief Checks if Password is safe, length lCase uCase, digits
*
* @return bool
*/
bool isPasswordSafe(const std::string& password);


/// \brief Launches the password manager.
/// \return The PasswordPass pointer created from createAccount() or loginIntoAccount().
/// \sa createAccount(), loginIntoAccount()
PasswordPass* launch();

/*
* @brief custom method for user input for password fields
* 
* @param type of date, usually website, login and  name
*
* @return string of correct data
*/
std::string inputType(const std::string type);

/*
* @brief Searches for a password in a given vector with given attributes
*
* @param vector<Password> in which search, SearchOption enum type
* 
* @return vector<Password> of passwords found with thoose parameters
*/
std::vector<Password> byAttribute(const std::vector<Password>& vec, const std::string nameOfAttribute, const SearchOption so);

//maybe delete
void quit(PasswordPass*& passwordManager);

/*
* @brief Checks if password is popular
*
* @param string password for which to check popularity
* 
* @return  bool
*/
bool isPasswordPopular(const std::string& password);

/*
* @brief Setter for 'other' field in class
*
* @param vec to set and object 
*
* @return  bool
*/
void setOthers(const std::vector<std::string> vec, PasswordPass* ps);