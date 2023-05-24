#pragma once
#include <string>

/// \class PasswordPass
/// \brief Object with password stored inside
class Password {
    std::string name;
    std::string pssword;
    std::string category;
    std::string website;
    std::string login;

public:
    Password(std::string name, std::string text, std::string category, std::string website, std::string login) : name(name), pssword(text), category(category), website(website), login(login) {} 


    std::string to_string() const {
        std::string result;
        result += "Name: " + name + " ";
        result += "Password: " + pssword + " ";
        result += "Category: " + category + "  ";
        result += "Website: " + website + " ";
        result += "Login: " + login + " ";
        return result;
    }

    // Getters maybe i dont need getter?
    std::string getName() const {
        return name;
    }

    std::string getPassword() const {
        return pssword;
    }

    std::string getCategory() const {
        return category;
    }

    std::string getWebsite() const {
        return website;
    }

    std::string getLogin() const {
        return login;
    }

    // Setters
    void setName(const std::string& newName) {
        name = newName;
    }

    void setText(const std::string& newText) {
        pssword = newText;
    }

    void setCategory(const std::string& newCategory) {
        category = newCategory;
    }

    void setWebsite(const std::string& newWebsite) {
        website = newWebsite;
    }

    void setLogin(const std::string& newLogin) {
        login = newLogin;
    }
};


