#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ncurses.h>

using namespace std;

// Function to get CPU usage
double get_cpu_usage() {
    static long long last_total_user, last_total_user_low, last_total_sys, last_total_idle;
    double percent;
    FILE* file = fopen("/proc/stat", "r");
    long long total_user, total_user_low, total_sys, total_idle;
    fscanf(file, "cpu %lld %lld %lld %lld", &total_user, &total_user_low, &total_sys, &total_idle);
    fclose(file);

    if (last_total_user != 0 || last_total_user_low != 0 || last_total_sys != 0 || last_total_idle != 0) {
        long long diff_user = total_user - last_total_user;
        long long diff_user_low = total_user_low - last_total_user_low;
        long long diff_sys = total_sys - last_total_sys;
        long long diff_idle = total_idle - last_total_idle;
        long long total = diff_user + diff_user_low + diff_sys + diff_idle;
        percent = (double)(diff_user + diff_user_low + diff_sys) * 100.0 / total;
    } else {
        percent = 0.0;
    }

    last_total_user = total_user;
    last_total_user_low = total_user_low;
    last_total_sys = total_sys;
    last_total_idle = total_idle;

    return percent;
}

// Function to get memory usage
pair<double, double> get_memory_usage() {
    ifstream file("/proc/meminfo");
    string line;
    double mem_total = 0, mem_available = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string key;
        double value;
        string unit;
        iss >> key >> value >> unit;
        if (key == "MemTotal:") mem_total = value;
        if (key == "MemAvailable:") mem_available = value;
    }
    file.close();
    double used = mem_total - mem_available;
    return {used / 1024, mem_total / 1024}; // MB
}

// Function to read system uptime
double read_uptime() {
    FILE* f = fopen("/proc/uptime", "r");
    double up = 0;
    fscanf(f, "%lf", &up);
    fclose(f);
    return up / 3600.0; // convert to hours
}

// Function to count processes
int count_processes() {
    int count = 0;
    system("ls /proc | grep '^[0-9]' > temp.txt");
    ifstream file("temp.txt");
    string line;
    while (getline(file, line)) count++;
    file.close();
    remove("temp.txt");
    return count;
}

int main() {
    initscr();             // Start ncurses mode
    noecho();              // Don't echo keypresses
    curs_set(FALSE);       // Hide cursor
    start_color();         // Enable color

    // Define colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    while (true) {
        clear(); // Clear the screen

        // Create boxes
        box(stdscr, 0, 0);
        mvprintw(1, 2, "=== SYSTEM MONITOR TOOL ===");

        double cpu = get_cpu_usage();
        auto mem = get_memory_usage();
        double uptime = read_uptime();
        int processes = count_processes();

        attron(COLOR_PAIR(1));
        mvprintw(3, 4, "[CPU]");
        attroff(COLOR_PAIR(1));
        mvprintw(3, 12, "%.2f%%", cpu);

        attron(COLOR_PAIR(2));
        mvprintw(5, 4, "[MEMORY]");
        attroff(COLOR_PAIR(2));
        mvprintw(5, 14, "Used: %.2f MB / Total: %.2f MB", mem.first, mem.second);

        attron(COLOR_PAIR(3));
        mvprintw(7, 4, "[UPTIME]");
        attroff(COLOR_PAIR(3));
        mvprintw(7, 14, "%.2f hours", uptime);

        attron(COLOR_PAIR(4));
        mvprintw(9, 4, "[PROCESSES]");
        attroff(COLOR_PAIR(4));
        mvprintw(9, 18, "%d running", processes);

        mvprintw(11, 2, "Press Ctrl + C to exit");
        refresh();

        this_thread::sleep_for(chrono::seconds(1));
    }

    endwin(); // End ncurses mode
    return 0;
}

