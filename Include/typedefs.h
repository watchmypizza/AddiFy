#pragma once
#include <string>
#include <variant>
#include <vector>

typedef std::string str_t;
typedef std::vector<str_t> strlist_t;

using stringvec = std::variant<strlist_t, str_t>;