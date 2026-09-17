#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <string>
#include <limits>
#include <vector>

int intgerinputfilter(const std::string& prompt);
std::string stringinputfilter(const std::string& prompt);

std::string liveSearch(const std::vector<std::string>& searchData);

#endif 
