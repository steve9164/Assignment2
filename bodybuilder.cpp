#include "bodybuilder.h"
#include "config_section.h"

#include <iostream>

#define ERR_STR ("WARNING: No/invalid config value for key: ")
#define ERR_DEF ("         Using default value: ")

void BodyBuilder::configError(ConfigSection* cs, std::string keyName, std::string def)
{
  std::cerr << ERR_STR << keyName;
  std::cerr << " in [" << cs->getName() << "]" << std::endl;
  std::cerr << ERR_DEF << def << std::endl;
}
