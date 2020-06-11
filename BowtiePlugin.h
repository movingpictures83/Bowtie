#ifndef BOWTIEPLUGIN_H
#define BOWTIEPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>

class BowtiePlugin : public Plugin
{
public: 
 std::string toString() {return "Bowtie";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
std::map<std::string, std::string> parameters;
};

#endif
