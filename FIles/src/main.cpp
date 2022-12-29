#include "main.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
    getLogger().info("Installed all hooks!");
}

int main() {
  // Initialize VR
  vr::InitVR();

  while (true) {
    // Check if the right trigger is pressed
    if (vr::IsTriggerPressed(vr::kRightTrigger)) {
      // Change the velocity by 10
      vr::SetVelocity(10.0f);

      // Wait for 1 second
      std::this_thread::sleep_for(std::chrono::seconds(1));

      // Set the velocity back to 0
      vr::SetVelocity(0.0f);
    }
  }

  // Shutdown VR
  vr::ShutdownVR();

  return 0;
}
