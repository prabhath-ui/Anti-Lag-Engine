#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// --- Process Profile ---
struct Process {
    int pid;
    std::string name;
    int memory_usage_mb;
    int priority_score;
    int pinned_cpu_core;
    bool is_foreground_game;
};

// --- Optimization Engine ---
void optimize_system(std::vector<Process>& processes, int& total_freed_ram) {
    std::cout << "\n[ANTI-LAG ENGAGED] Optimizing System Resources...\n";
    std::cout << "===========================================================\n";

    total_freed_ram = 0;

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
            total_freed_ram += saved_ram;
            
            std::cout << "Throttled " << app.name << " -> Priority Level [1], Moved to Core [1] | Freed " << saved_ram << " MB RAM\n";
        }
    }
    std::cout << "===========================================================\n";
}

// --- DAY 4: THERMAL MONITOR & HARDWARE SAFEGUARD ---
void check_thermal_status(double current_temp_c, std::vector<Process>& processes) {
    std::cout << "\n[THERMAL DAEMON] Scanning CPU Sensors...\n";
    std::cout << "Current CPU Temperature: " << current_temp_c << "°C\n";

    if (current_temp_c >= 85.0) {
        std::cout << "⚠️  CRITICAL WARNING: CPU Temperature exceeded 85°C threshold!\n";
        std::cout << "⚠️  ENGAGING EMERGENCY THERMAL SAFEGUARD...\n";
        
        // Relief mechanism: Drop background process priority further to cool down hardware
        for (auto& app : processes) {
            if (!app.is_foreground_game) {
                app.pinned_cpu_core = -1; // Unpin from Core 1 to distribute thermal load across all idle cores
            }
        }
        std::cout << "-> Unpinned background processes to spread thermal load across idle cores.\n";
    } else {
        std::cout << "✅ Thermal levels stable. No emergency intervention needed.\n";
    }
}

// --- Telemetry Dashboard ---
void display_telemetry(int initial_bg_ram, int total_freed_ram, double cpu_temp) {
    double percentage_saved = ((double)total_freed_ram / initial_bg_ram) * 100.0;

    std::cout << "\n===========================================================\n";
    std::cout << "         📊 DAY 4: SYSTEM TELEMETRY & HARDWARE REPORT       \n";
    std::cout << "===========================================================\n";
    std::cout << " Initial Background RAM Load : " << initial_bg_ram << " MB\n";
    std::cout << " Total Memory Reclaimed     : " << total_freed_ram << " MB\n";
    std::cout << " Background RAM Reduction   : " << std::fixed << std::setprecision(1) << percentage_saved << "%\n";
    std::cout << " Core Pinning Status        : Active (Game: Core 0 | BG: Core 1)\n";
    std::cout << " CPU Package Temp           : " << cpu_temp << "°C " << (cpu_temp >= 85.0 ? "[OVERHEAT WARNING]" : "[NOMINAL]") << "\n";
    std::cout << " Target App Performance     : MAXIMUM BOOST PRESERVED\n";
    std::cout << "===========================================================\n\n";
}

int main() {
    std::vector<Process> running_apps;

    running_apps.push_back({101, "Chrome (50 Tabs Open)", 1200, 3, -1, false});
    running_apps.push_back({204, "Spotify Music Stream", 350, 3, -1, false});
    running_apps.push_back({312, "Antivirus Background Scan", 800, 4, -1, false});
    running_apps.push_back({777, "Cyberpunk 2077 (Game)", 2500, 3, -1, true});

    int initial_bg_ram = 0;
    for (const auto& app : running_apps) {
        if (!app.is_foreground_game) {
            initial_bg_ram += app.memory_usage_mb;
        }
    }

    // Run Engine
    int total_freed_ram = 0;
    optimize_system(running_apps, total_freed_ram);

    // Simulate high thermal load (88.5°C) to test emergency daemon
    double simulated_cpu_temp = 88.5; 
    check_thermal_status(simulated_cpu_temp, running_apps);

    // Display Updated Telemetry
    display_telemetry(initial_bg_ram, total_freed_ram, simulated_cpu_temp);

    return 0;
}