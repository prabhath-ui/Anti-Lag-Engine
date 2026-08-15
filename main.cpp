#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

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
void optimize_system(std::vector<Process>& processes, int& total_freed_ram) {
    std::cout << "\n[ANTI-LAG ENGAGED] Optimizing System Resources...\n";
    std::cout << "===========================================================\n";

    total_freed_ram = 0; // Reset counter

    for (auto& app : processes) {
        if (app.is_foreground_game) {
            app.priority_score = 5;
            app.pinned_cpu_core = 0;
            std::cout << "Boosted " << app.name << " -> Priority Level [5], Locked to Core [0]\n";
        } 
        else {
            app.priority_score = 1;
            app.pinned_cpu_core = 1;
            
            int saved_ram = app.memory_usage_mb * 0.7;
            app.memory_usage_mb -= saved_ram;
            total_freed_ram += saved_ram; // Accumulate total reclaimed memory
            
            std::cout << "Throttled " << app.name << " -> Priority Level [1], Moved to Core [1] | Freed " << saved_ram << " MB RAM\n";
        }
    }
    std::cout << "===========================================================\n";
}
// --- STEP 3: DAY 3 TELEMETRY & SYSTEM DIAGNOSTIC DASHBOARD ---
void display_telemetry(int initial_bg_ram, int total_freed_ram) {
    double percentage_saved = ((double)total_freed_ram / initial_bg_ram) * 100.0;

    std::cout << "\n===========================================================\n";
    std::cout << "         📊 DAY 3: SYSTEM TELEMETRY & HEALTH REPORT       \n";
    std::cout << "===========================================================\n";
    std::cout << " Initial Background RAM Load : " << initial_bg_ram << " MB\n";
    std::cout << " Total Memory Reclaimed     : " << total_freed_ram << " MB\n";
    std::cout << " Background RAM Reduction   : " << std::fixed << std::setprecision(1) << percentage_saved << "%\n";
    std::cout << " Core Pinning Status        : Active (Game: Core 0 | BG: Core 1)\n";
    std::cout << " Target App Performance     : MAXIMUM BOOST PRESERVED\n";
    std::cout << "===========================================================\n\n";
}

// --- STEP 4: Main Execution ---
int main() {
    std::vector<Process> running_apps;

    running_apps.push_back({101, "Chrome (50 Tabs Open)", 1200, 3, -1, false});
    running_apps.push_back({204, "Spotify Music Stream", 350, 3, -1, false});
    running_apps.push_back({312, "Antivirus Background Scan", 800, 4, -1, false});
    running_apps.push_back({777, "Cyberpunk 2077 (Game)", 2500, 3, -1, true});

    // Calculate initial background memory footprint before optimization
    int initial_bg_ram = 0;
    for (const auto& app : running_apps) {
        if (!app.is_foreground_game) {
            initial_bg_ram += app.memory_usage_mb;
        }
    }

    std::cout << "=== BEFORE OPTIMIZATION ===" << std::endl;
    for (const auto& app : running_apps) {
        std::cout << "App: " << app.name << " | RAM: " << app.memory_usage_mb 
                  << " MB | Priority: " << app.priority_score << " | Core: " << app.pinned_cpu_core << "\n";
    }

    // Run Optimization
    int total_freed_ram = 0;
    optimize_system(running_apps, total_freed_ram);

    // Run Telemetry Dashboard
    display_telemetry(initial_bg_ram, total_freed_ram);

    return 0;
}