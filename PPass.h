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
    std::string pathToFile;

private:
    /// \brief Private constructor to initialize the password list.
    /// \param list The list of decrypted passwords.
    PasswordPass(std::vector<Password> list, std::string pathToFile) : passwordList(list), pathToFile(pathToFile) {}

public:
    /// \brief Creates a new password manager account.
    /// \sa loginIntoAccount(), launch()
    static void createAccount();

    /// \brief Logs into an existing password manager account.
    /// \return The PasswordPass object representing the logged-in account.
    /// \sa createAccount(), launch()
    static PasswordPass loginIntoAccount();

    /// \brief Launches the password manager.
    /// \return The PasswordPass object created from createAccount() and loginIntoAccount().
    /// \sa createAccount(), loginIntoAccount()
    static PasswordPass launch();

    ~PasswordPass();
};

