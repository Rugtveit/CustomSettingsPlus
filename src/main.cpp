#include "main.hpp"

static ModInfo modInfo; 


Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}


Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}


extern "C" void setup(ModInfo& info) {
    info.id = "customsettingsplus";
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); 
    getLogger().info("Completed setup!");
}


extern "C" void load() {
    il2cpp_functions::Init();
    
    getLogger().info("Installing hooks...");
    
    getLogger().info("Installed all hooks!");
}