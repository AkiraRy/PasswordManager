#pragma once
#include <string>
#include <vector>
#include <map>
#include "Password.h"


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


    // Function to populate the passwordMap based on passwordList categories
    void populatePasswordMap();

    // Function to retrieve all categories available
    std::vector<std::string> getAllCategories() const;

    // Function to retrieve passwords by category
    const std::vector<Password>& getPasswordsByCategory(const std::string& category) const;


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


/// \brief Launches the password manager.
/// \return The PasswordPass object created from createAccount() and loginIntoAccount().
/// \sa createAccount(), loginIntoAccount()
PasswordPass* launch();
