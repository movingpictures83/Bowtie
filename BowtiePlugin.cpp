#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "BowtiePlugin.h"

void BowtiePlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 std::cout << file << std::endl;
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }

}

void BowtiePlugin::run() {}

void BowtiePlugin::output(std::string file) {
 std::string outputfile = file;
 std::string myCommand = "";
myCommand +=  "bowtie2-build";
myCommand += " ";
myCommand += std::string(PluginManager::prefix())+parameters["contigs"];
myCommand += " ";
myCommand += outputfile+".idx";
system(myCommand.c_str());
myCommand = "";
myCommand += "bowtie2";
myCommand += " ";
myCommand += "-p 1";
myCommand += " ";
myCommand += "-x";
myCommand += " ";
myCommand += outputfile+".idx";
myCommand += " ";
if (parameters.count("sequences") != 0) {
myCommand += "-U";
myCommand += " ";
myCommand += parameters["sequences"] + " ";
}
else {
myCommand += "-1";
myCommand += " ";
myCommand += parameters["sequences1"] + " ";
myCommand += "-2";
myCommand += " ";
myCommand += parameters["sequences2"] + " ";
}
myCommand += "-S";
myCommand += " ";
myCommand += outputfile+".sam0";
myCommand += " ";
myCommand += "1>"+outputfile+".sam0.bowtie2.out 2>"+outputfile+".sam0.bowtie2.err";
 system(myCommand.c_str());
}

PluginProxy<BowtiePlugin> BowtiePluginProxy = PluginProxy<BowtiePlugin>("Bowtie", PluginManager::getInstance());
