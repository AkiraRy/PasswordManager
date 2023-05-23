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
    std::string pathToFile;
    std::vector<int> timestamp;
    std::map<std::string, std::vector<Password>> passwordMap; // New map, category - passwords listt

private:
    /// \brief Private constructor to initialize the password list.
    /// \param list The list of decrypted passwords.
    PasswordPass(std::string pathToFile, std::vector<std::string> other);

    /// \brief Private method to handle login with a file path.
    /// \param manualPath - path from folder
    static PasswordPass* loginWithPath(std::string autoPath);

    /// \brief Login by choosing file from a folder.
    static PasswordPass* loginFromFolder();


public:

    void changePassword();

    void removeDirectory();

    void addCategory();


    void addPassword();

    void sortPasswords();


    // Function to retrieve passwords by category
    std::vector<Password> getPasswordsByCategory(const std::string& category);


    const std::map<std::string, std::vector<Password>>& getPasswordMap() const {
        return passwordMap;
    }


    void searchPassword();


    // Function to populate the passwordMap based on passwordList categories
    void populatePasswordMap();

    // Function to retrieve all categories available
    std::vector<std::string> getAllCategories() const;

    void showCategories();


    /// \brief Creates a new password manager account.
    /// \sa loginIntoAccount(), launch()
    static void createAccount();

    /// \brief Logs into an existing password manager account.
    /// \return The PasswordPass object representing the logged-in account.
    /// \sa createAccount(), launch()
    static PasswordPass* loginIntoAccount();

    

    void setPasswordList(const std::vector<Password>& list) { passwordList = list; }

    const std::vector<Password>& getPasswordList() const {
        return passwordList;
    }

    const std::vector<std::string>& getOther() const {
        return other;
    }

    const std::string& getPathToFile() const {
        return pathToFile;
    }

    void showPasswords();


    ~PasswordPass();
};

void simulateApp(PasswordPass*& ppass);


/// \brief Launches the password manager.
/// \return The PasswordPass object created from createAccount() and loginIntoAccount().
/// \sa createAccount(), loginIntoAccount()
PasswordPass* launch();

std::vector<Password> byAttribute(const std::vector<Password> vec, const std::string nameOfAttribute, const SearchOption so);

void quit(PasswordPass*& passwordManager);

bool isPasswordPopular(const std::string& password);