#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// --- System Operating Modes ---
enum OperatingMode {
    GAMING_BOOST,
    BATTERY_SAVER
};

// --- Process Profile (PCB) ---
struct Process {
    int pid;
    std::string name;
    int memory_usage_mb;
    int priority_score;
    int pinned_cpu_core;
    bool is_foreground_game;
};

// --- Day 5 Multi-Mode Optimization Engine ---
void optimize_system(std::vector<Process>& processes, int& total_freed_ram, OperatingMode mode) {
    total_freed_ram = 0;

    std::cout << "\n===========================================================\n";
    if (mode == GAMING_BOOST) {
        std::cout << "[ENGINE MODE: GAMING BOOST ACTIVE]\n";
    } else {
        std::cout << "[ENGINE MODE: BATTERY SAVER ACTIVE]\n";
    }
    std::cout << "===========================================================\n";

    for (auto& app : processes) {
        if (mode == GAMING_BOOST) {
            if (app.is_foreground_game) {
                app.priority_score = 5;
                app.pinned_cpu_core = 0;
                std::cout << "[BOOST] " << app.name << " -> Priority: [5] | Core: Locked [0]\n";
            } else {
                app.priority_score = 1;
                app.pinned_cpu_core = 1;
                
                int saved_ram = app.memory_usage_mb * 0.7;
                app.memory_usage_mb -= saved_ram;
                total_freed_ram += saved_ram;
                
                std::cout << "[THROTTLE] " << app.name << " -> Priority: [1] | Core: [1] | Freed: " << saved_ram << " MB\n";
            }
        } 
        else if (mode == BATTERY_SAVER) {
            // Under Battery Saver, cap ALL process priorities and unpin cores to save power
            app.priority_score = 1;
            app.pinned_cpu_core = -1;
            
            int saved_ram = app.memory_usage_mb * 0.4;
            app.memory_usage_mb -= saved_ram;
            total_freed_ram += saved_ram;

            std::cout << "[SAVER] " << app.name << " -> Power Capped | Priority: [1] | Core: [Unpinned]\n";
        }
    }
    std::cout << "===========================================================\n";
}

// --- Thermal Monitor Safeguard ---
void check_thermal_status(double current_temp_c, std::vector<Process>& processes) {
    std::cout << "\n[THERMAL DAEMON] Scanning CPU Core Sensors...\n";
    std::cout << "Current Package Temp: " << current_temp_c << " C\n";

    if (current_temp_c >= 85.0) {
        std::cout << "!! WARNING: High Temp (>85 C) Detected! Engaging Emergency Safeguard...\n";
        for (auto& app : processes) {
            if (!app.is_foreground_game) {
                app.pinned_cpu_core = -1; // Unpin to spread thermal load
            }
        }
        std::cout << "-> Background processes unpinned across idle cores to prevent thermal throttling.\n";
    } else {
        std::cout << "[OK] Thermal levels nominal.\n";
    }
}

// --- Production Telemetry Dashboard ---
void display_telemetry(int initial_bg_ram, int total_freed_ram, double cpu_temp, OperatingMode mode) {
    double percentage_saved = (initial_bg_ram > 0) ? ((double)total_freed_ram / initial_bg_ram) * 100.0 : 0.0;

    std::cout << "\n===========================================================\n";
    std::cout << "          DAY 5: ANTI-LAG ENGINE FINAL REPORT              \n";
    std::cout << "===========================================================\n";
    std::cout << " Active Profile Mode       : " << (mode == GAMING_BOOST ? "GAMING BOOST" : "BATTERY SAVER") << "\n";
    std::cout << " Initial Background RAM    : " << initial_bg_ram << " MB\n";
    std::cout << " Total Memory Reclaimed    : " << total_freed_ram << " MB\n";
    std::cout << " RAM Footprint Reduction   : " << std::fixed << std::setprecision(1) << percentage_saved << "%\n";
    std::cout << " Core Pinning Status       : " << (mode == GAMING_BOOST ? "Active (Core 0/1)" : "Disabled (Power Save)") << "\n";
    std::cout << " CPU Temperature           : " << cpu_temp << " C " << (cpu_temp >= 85.0 ? "[OVERHEAT SAFEGUARD ACTIVE]" : "[NOMINAL]") << "\n";
    std::cout << "===========================================================\n\n";
}

int main() {
    std::vector<Process> running_apps = {
        {101, "Chrome (50 Tabs Open)", 1200, 3, -1, false},
        {204, "Spotify Music Stream", 350, 3, -1, false},
        {312, "Antivirus Background Scan", 800, 4, -1, false},
        {777, "Cyberpunk 2077 (Game)", 2500, 3, -1, true}
    };

    int initial_bg_ram = 0;
    for (const auto& app : running_apps) {
        if (!app.is_foreground_game) {
            initial_bg_ram += app.memory_usage_mb;
        }
    }

    // Select Engine Mode
    OperatingMode current_mode = GAMING_BOOST; // Change to BATTERY_SAVER to test battery mode!

    int total_freed_ram = 0;
    optimize_system(running_apps, total_freed_ram, current_mode);

    double simulated_cpu_temp = 88.5;
    check_thermal_status(simulated_cpu_temp, running_apps);

    display_telemetry(initial_bg_ram, total_freed_ram, simulated_cpu_temp, current_mode);

    return 0;
}