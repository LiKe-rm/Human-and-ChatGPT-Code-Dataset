#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

bool ParseArguments(int argc, char* argv[], std::string& registry_key, std::string& value_name, std::string& output_file)
{
    if (argc != 4)
    {
        std::cout << "Usage: reg_export.exe <registry_key> <value_name> <output_file>" << std::endl;
        return false;
    }

    registry_key = argv[1];
    value_name = argv[2];
    output_file = argv[3];

    return true;
}

HKEY StringToHKEY(const std::string& registry_key)
{
    if (registry_key == "HKEY_CLASSES_ROOT") return HKEY_CLASSES_ROOT;
    if (registry_key == "HKEY_CURRENT_USER") return HKEY_CURRENT_USER;
    if (registry_key == "HKEY_LOCAL_MACHINE") return HKEY_LOCAL_MACHINE;
    if (registry_key == "HKEY_USERS") return HKEY_USERS;
    if (registry_key == "HKEY_CURRENT_CONFIG") return HKEY_CURRENT_CONFIG;

    return nullptr;
}

bool ReadRegistryValue(const std::string& registry_key, const std::string& value_name, std::vector<unsigned char>& bData)
{
    HKEY hKey = StringToHKEY(registry_key);
    if (hKey == nullptr)
    {
        std::cout << "Error: Invalid registry key." << std::endl;
        return false;
    }

    HKEY hOpenedKey;
    if (RegOpenKeyEx(hKey, value_name.c_str(), 0, KEY_READ, &hOpenedKey) != ERROR_SUCCESS)
    {
        std::cout << "Error: Failed to open registry key." << std::endl;
        return false;
    }

    DWORD dataSize;
    if (RegQueryValueEx(hOpenedKey, value_name.c_str(), nullptr, nullptr, nullptr, &dataSize) != ERROR_SUCCESS)
    {
        std::cout << "Error: Failed to query registry value size." << std::endl;
        return false;
    }

    bData.resize(dataSize);
    if (RegQueryValueEx(hOpenedKey, value_name.c_str(), nullptr, nullptr, bData.data(), &dataSize) != ERROR_SUCCESS)
    {
        std::cout << "Error: Failed to read registry value data." << std::endl;
        return false;
    }

    RegCloseKey(hOpenedKey);

    return true;
}

bool WriteToFile(const std::string& output_file, const std::vector<unsigned char>& bData)
{
    std::ofstream ofs(output_file, std::ios::binary);
    if (!ofs)
    {
        std::cout << "Error: Unable to open output file." << std::endl;
        return false;
    }

    ofs.write(reinterpret_cast<const char*>(bData.data()), bData.size());
    ofs.close();

    return true;
}

int main(int argc, char* argv[])
{
    std::cout << "Welcome to reg_export.exe!" << std::endl;

    std::string registry_key, value_name, output_file;
    if (!ParseArguments(argc, argv, registry_key, value_name, output_file)) return 1;

    std::vector<unsigned char> bData;
    if (!ReadRegistryValue(registry_key, value_name, bData)) return 2;
    if (!WriteToFile(output_file, bData))
    {
        std::cout << "Error: Failed to write data to output file." << std::endl;
        return 3;
    }

    std::cout << "Successfully exported registry value to output file: " << output_file << std::endl;
    return 0;
}

