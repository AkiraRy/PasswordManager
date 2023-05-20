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

private:
    /// \brief Private constructor to initialize the password list.
    /// \param list The list of decrypted passwords.
    PasswordPass(std::string pathToFile, std::vector<std::string> other);

public:
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


    ~PasswordPass();
};


/// \brief Launches the password manager.
/// \return The PasswordPass object created from createAccount() and loginIntoAccount().
/// /// \sa createAccount(), loginIntoAccount()
PasswordPass* launch();
