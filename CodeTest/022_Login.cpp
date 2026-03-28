#include <string>
#include <vector>
#include <unordered_map>

std::string Login(std::vector<std::string> id_pw, std::vector<std::vector<std::string>> db) {

    for(const auto& users : db)
    {
        if (0 == (id_pw[0].compare(users[0])) )
        {
            if (0 == (id_pw[1].compare(users[1])))
                return "login";
            else
                return "wrong pw";
        }
    }
    return "fail";
}

std::string LoginFullDB(std::vector<std::string> id_pw, std::vector<std::vector<std::string>> db) {

    std::unordered_map<std::string, std::string> mp;

    for(const auto& user : db)
        mp[user[0]] = user[1];
    
    auto it = mp.find(id_pw[0]);
   
    if(it == mp.end())
        return "fail";

    if(it->second == id_pw[1])
        return "login";
    else 
        return "worng pw";
}