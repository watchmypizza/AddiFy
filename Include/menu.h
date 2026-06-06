#pragma once
#include <yaml-cpp/yaml.h>
#include "typedefs.h"

int menu(void);
YAML::Node loadYaml(const str_t& path);
void RAMYAML(void);