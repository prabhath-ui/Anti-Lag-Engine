#include <iostream>
#include <string>
#include <vector>

// --- STEP 1: Define the Process Profile ---
struct Process {
    int pid;                   // Unique Process ID
    std::string name;          // App Name
    int memory_usage_mb;       // RAM usage
    int priority_score;        // 1 = Lowest, 5 = Highest
    int pinned_cpu_core;       // -1 = Any Core, 0 = High-Perf Core, 1 = Efficiency Core
    bool is_foreground_game;   // Is this the game needing a boost?
};

// --- STEP 2: The Day 2 Optimization Engine ---
// We use 'std::vector<Process>&' (Pass by Reference) so we modify the REAL processes in memory!
void optimize_system(std::vector<Process>& processes) {
    std::cout << "\n[ANTI-LAG ENGAGED] Optimizing System Resources...\n";
    std::cout << "===========================================================\n";

    for (auto& app : processes) {
        if (app.is_foreground_game) {
            // Give max priority and pin to High-Performance Core 0
            app.priority_score = 5;
            app.pinned_cpu_core = 0;
            std::cout << "Boosted " << app.name << " -> Priority Level [5], Locked to Core [0]\n";
        } 
        else {
            // Throttle priority, move to Efficiency Core 1, and reclaim 70% background RAM
            app.priority_score = 1;
            app.pinned_cpu_core = 1;
            
            int saved_ram = app.memory_usage_mb * 0.7;
            app.memory_usage_mb -= saved_ram;
            
            std::cout << "Throttled " << app.name << " -> Priority Level [1], Moved to Core [1] | Freed " << saved_ram << " MB RAM\n";
        }
    }
    std::cout << "===========================================================\n\n";
}

// --- STEP 3: The Main Simulation Routine ---
int main() {
    std::vector<Process> running_apps;

    running_apps.push_back({101, "Chrome (50 Tabs Open)", 1200, 3, -1, false});
    running_apps.push_back({204, "Spotify Music Stream", 350, 3, -1, false});
    running_apps.push_back({312, "Antivirus Background Scan", 800, 4, -1, false});
    running_apps.push_back({777, "Cyberpunk 2077 (Game)", 2500, 3, -1, true});

    std::cout << "=== BEFORE OPTIMIZATION ===" << std::endl;
    for (const auto& app : running_apps) {
        std::cout << "App: " << app.name << " | RAM: " << app.memory_usage_mb 
                  << " MB | Priority: " << app.priority_score << " | CPU Core: " << app.pinned_cpu_core << "\n";
    }

    // Run our custom Day 2 Anti-Lag Engine!
    optimize_system(running_apps);

    std::cout << "=== AFTER OPTIMIZATION ===" << std::endl;
    for (const auto& app : running_apps) {
        std::cout << "App: " << app.name << " | RAM: " << app.memory_usage_mb 
                  << " MB | Priority: " << app.priority_score << " | CPU Core: " << app.pinned_cpu_core << "\n";
    }

    return 0;
}