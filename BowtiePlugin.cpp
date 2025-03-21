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
   if (key.length() == 0) break;
   ifile >> value;
   if (value.length() == 0) break;
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
myCommand += "-q -1";
myCommand += " ";
myCommand += parameters["sequences1"] + " ";
myCommand += "-2";
myCommand += " ";
myCommand += parameters["sequences2"] + " ";
}
if (parameters.count("threads") != 0) {
myCommand += "--threads";
myCommand += " ";
myCommand += parameters["threads"] + " ";
}
if (parameters.count("all") != 0 && parameters["all"] == "True") {
	myCommand += "-a ";
}
if (parameters.count("local") != 0 && parameters["local"] == "True") {
	myCommand += "--local ";
}
if (parameters.count("veryfastlocal") != 0 && parameters["veryfastlocal"] == "True") {
	myCommand += "--very-fast-local ";
}
if (parameters.count("nodiscordant") != 0 && parameters["nodiscordant"] == "True") {
	myCommand += "--no-discordant ";
}
if (parameters.count("verysensitive") != 0 && parameters["verysensitive"] == "True") {
	myCommand += "--very-sensitive ";
}
if (parameters.count("nomixed") != 0 && parameters["nomixed"] == "True") {
	myCommand += "--no-mixed ";
}
if (parameters.count("nounal") != 0 && parameters["nounal"] == "True") {
	myCommand += "--no-unal ";
}
if (parameters.count("reorder") != 0 && parameters["reorder"] == "True") {
	myCommand += "--reorder ";
}
myCommand += "-S";
myCommand += " ";
myCommand += outputfile+".sam0";
myCommand += " ";
myCommand += "1>"+outputfile+".sam0.bowtie2.out 2>"+outputfile+".sam0.bowtie2.err";
std::cout << myCommand << std::endl;
system(myCommand.c_str());
}

PluginProxy<BowtiePlugin> BowtiePluginProxy = PluginProxy<BowtiePlugin>("Bowtie", PluginManager::getInstance());
