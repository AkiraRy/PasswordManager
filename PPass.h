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
    std::vector<Password> passwordList;

    std::vector<std::string> other;

    std::string password;

    std::string pathToFile;

    std::vector<int> timestamp;

    std::map<std::string, std::vector<Password>> passwordMap; // New map, category - passwords listt

private:
    /// \brief Private constructor to initialize the password list.
    /// \param list The list of decrypted passwords.
    PasswordPass(std::string pathToFile, std::string password);

    /// \brief Private method to handle login with a file path.
    /// \param manualPath - path from folder
    static PasswordPass* loginWithPath(std::string autoPath);

    /// \brief Login by choosing file from a folder.
    static PasswordPass* loginFromFolder();


public:
    /**
    * @brief Sets additional string data.
    * @param vec The vector of strings.
    */
    void setOther(std::vector<std::string> vec) {
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

    //continue
    void passwordStatistics(const std::string password);

    bool usedBefore(const std::string password);

    void deletePassword();

    //done
    void editPassword();

    //done
    void deleteCategory();

    //done
    void addCategory();

    //done
    void addPassword();

    void sortPasswords();

    void helpSort(std::vector<std::string> sortFields);

    // Function to retrieve passwords by category
    std::vector<Password> getPasswordsByCategory(const std::string& category);


    const std::map<std::string, std::vector<Password>>& getPasswordMap() const {
        return passwordMap;
    }

    //done
    void searchPassword();


    // Function to populate the passwordMap based on passwordList categories
    void populatePasswordMap();

    // Function to retrieve all categories available
    std::vector<std::string> getAllCategories() const;

    void showCategories();


    /// \brief Creates a new password manager account.
    /// \sa loginIntoAccount(), launch()
    static PasswordPass* createAccount();

    /// \brief Logs into an existing password manager account.
    /// \return The PasswordPass object representing the logged-in account.
    /// \sa createAccount(), launch()
    static PasswordPass* loginIntoAccount();

    

    void setPasswordList(const std::vector<Password>& list) { passwordList = list; }

    const std::vector<Password>& getPasswordList() const {
        return passwordList;
    }

    void showOther();

    const std::vector<std::string>& getOther() const {
        return other;
    }

    const std::string& getPathToFile() const {
        return pathToFile;
    }
    const std::string& getPassword() const {
        return password;
    }

    void showPasswords();


    ~PasswordPass();
};

std::vector<std::string> templatePassword();

void simulateApp(PasswordPass*& ppass);

bool isPasswordSafe(const std::string& password);


/// \brief Launches the password manager.
/// \return The PasswordPass object created from createAccount() and loginIntoAccount().
/// \sa createAccount(), loginIntoAccount()
PasswordPass* launch();

std::string inputType(std::string type);

std::vector<Password> byAttribute(const std::vector<Password> vec, const std::string nameOfAttribute, const SearchOption so);

void quit(PasswordPass*& passwordManager);

bool isPasswordPopular(const std::string& password);

void setOthers(std::vector<std::string> vec);