#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "value: " + key;
    }
};


class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots) : real_db_(real_object), counter(shots) {}
    
    std::string GetData(const std::string& key) noexcept 
    {
        if (cache_.find(key) == cache_.end() && counter > 0) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
            counter--;
        }
        else if (counter > 0) {
            std::cout << "Get from cache\n";
            counter--;
        }
        else
            return "error";
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
    size_t counter;
};


int main() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2); // с помощью std::addressof передаем адрес в констурктор CacheProxyDB
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}