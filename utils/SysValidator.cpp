#include "../headers/SysValidator.h"
#include <filesystem>

int SysValidator::DirectoryValidator(std::string directoryPath) {
  std::filesystem::directory_entry entry{directoryPath};
  return entry.exists();
}
