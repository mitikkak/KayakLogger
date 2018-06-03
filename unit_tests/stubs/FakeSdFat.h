
#include <string>
#include <vector>
class SdFat
{
public:
    bool begin(const int cs) const;
    bool mkdir(const char* const) const;
    void add(std::string name);
    bool exists(const char* const) const;
private:
    std::vector<std::string> files;
};
