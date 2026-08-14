#include <iostream>
#include <string>
#include <vector>

// --- STEP 1: Define the Process Profile ---
// A struct lets us group different types of information together under one name.
struct Process {
    int pid;                   // Process ID: A unique number the OS uses to identify an app
    std::string name;          // The name of the application
    int memory_usage_mb;       // How much RAM memory the app is currently eating up
    int priority_score;        // 1 = Lowest priority, 5 = Highest priority
    int pinned_cpu_core;       // The specific CPU core this app is forced to run on (-1 means any core)
    bool is_foreground_game;   // Tells us if this is the heavy game the user wants to boost
};

// --- STEP 2: The Main Simulation Routine ---
int main() {
    // A vector is a dynamic list in C++. It can grow or shrink automatically.
    // We are creating a list called 'running_apps' to hold our Process structs.
    std::vector<Process> running_apps;

    // Let's populate our laptop's memory with a few running background apps
    // Syntax format: {pid, name, memory_usage_mb, priority_score, pinned_cpu_core, is_foreground_game}
    running_apps.push_back({101, "Chrome (50 Tabs Open)", 1200, 3, -1, false});
    running_apps.push_back({204, "Spotify Music Stream", 350, 3, -1, false});
    running_apps.push_back({312, "Antivirus Background Scan", 800, 4, -1, false});
    
    // Now let's add the heavy game that the user just launched
    running_apps.push_back({777, "Cyberpunk 2077 (Game)", 2500, 3, -1, true});

    std::cout << "=== STATUS: Laptop Memory Scanned (Day 1) ===" << std::endl;
    std::cout << "Listing all running applications...\n" << std::endl;

    // This loop goes through our list of running apps one by one and prints their status
    for (const auto& app : running_apps) {
        std::cout << "App Name : " << app.name << "\n";
        std::cout << "PID      : [" << app.pid << "]\n";
        std::cout << "Memory   : " << app.memory_usage_mb << " MB\n";
        std::cout << "Priority : Level " << app.priority_score << "\n";
        std::cout << "Status   : " << (app.is_foreground_game ? "🎮 ACTIVE GAME (Needs Boost)" : "💤 Background Process") << "\n";
        std::cout << "------------------------------------------" << std::endl;
    }

    return 0;
}