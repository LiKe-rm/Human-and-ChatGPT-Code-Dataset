#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include "panda/plugin.h"
#include "panda/plugin_plugin.h"
#include "panda/rr/rr_log.h"
#include "panda/plugin_info.h"
#include "panda/rr/rr.h"
#include "panda/rr/rr_cpu.h"
#include "panda/common.h"
#include "panda/plugin_util.h"
#include "panda/rr/rr_control.h"
#include "panda/rr/rr_translate.h"
#include "panda/rr/rr_cpu.h"
#include "panda/rr/rr_log.h"
#include "panda/rr/rrsyscall.h"

using namespace std;

#define PLUGIN_NAME "ASID Tracker Plugin"
#define OUTPUT_FILE_NAME "asidstory"

static ofstream output_file;

static uint32_t total_instructions = 0;
static uint32_t current_asid = 0;
static uint32_t current_start_instruction = 0;

static vector<pair<uint32_t, uint32_t>> asid_data;

// This function is called when the plugin is loaded
extern "C" bool init_plugin(void *self) {
    panda_require("rr");

    // Open the output file
    output_file.open(OUTPUT_FILE_NAME);
    if (!output_file.is_open()) {
        printf("Failed to open output file '%s'\n", OUTPUT_FILE_NAME);
        return false;
    }

    // Set up the output file header
    output_file << "ASID\tStart Instruction\tEnd Instruction\tLifetime (%)\n";

    return true;
}

// This function is called when the plugin is unloaded
extern "C" void uninit_plugin(void *self) {
    // Close the output file
    output_file.close();
}

// This function is called on every basic block translation
bool on_translate(TranslationBlock *tb) {
    // Increment the total instruction count
    total_instructions += tb->size;

    // Get the current ASID
    uint32_t new_asid = panda_current_asid();

    // If the ASID has changed
    if (new_asid != current_asid) {
        // If we were tracking a previous ASID
        if (current_asid != 0) {
            // Add the current ASID data to the vector
            asid_data.push_back(make_pair(current_start_instruction, total_instructions));

            // Output the ASID data to the file
            output_file << current_asid << "\t" << current_start_instruction << "\t"
                        << total_instructions << "\t"
                        << ((total_instructions - current_start_instruction) * 100.0 / total_instructions)
                        << endl;

            // Reset the start instruction for the new ASID
            current_start_instruction = total_instructions;
        }

        // Update the current ASID
        current_asid = new_asid;
    }

    return true;
}

// This function is called on every instruction executed
void on_execute(TranslationBlock *tb) {
    // Do nothing
}

// This function is called on every system call
void on_syscall(TranslationBlock *tb, uint32_t pc) {
    // Do nothing
}

// This function is called on every basic block exit
bool on_bb_exit(CPUState *cpu, TranslationBlock *tb) {
    return true;
}

// This function is called on every interrupt
void on_interrupt(CPUState *cpu, int intno) {
    // Do nothing
}

//
// This function is called on every replay exit
void on_replay_exit() {
// If we were tracking an ASID
if (current_asid != 0) {
// Add the current ASID data to the vector
asid_data.push_back(make_pair(current_start_instruction, total_instructions));
    // Output the ASID data to the file
    output_file << current_asid << "\t" << current_start_instruction << "\t"
                << total_instructions << "\t"
                << ((total_instructions - current_start_instruction) * 100.0 / total_instructions)
                << endl;
}

// Generate the asciiart graph
const int graph_width = 80;
const int graph_height = 20;
const int graph_scale = 10;

vector<uint32_t> lifetimes;
for (auto asid : asid_data) {
    lifetimes.push_back(asid.second - asid.first);
}

uint32_t max_lifetime = *max_element(lifetimes.begin(), lifetimes.end());
uint32_t lifetime_scale = (max_lifetime + graph_height - 1) / graph_height;

vector<vector<char>> graph(graph_height, vector<char>(graph_width, ' '));

for (int i = 0; i < asid_data.size(); i++) {
    uint32_t lifetime = asid_data[i].second - asid_data[i].first;
    uint32_t lifetime_height = lifetime / lifetime_scale;
    uint32_t lifetime_width = lifetime_height / graph_scale;
    uint32_t start_width = asid_data[i].first / total_instructions * graph_width;
    uint32_t end_width = asid_data[i].second / total_instructions * graph_width;

    for (int x = start_width; x < end_width; x++) {
        for (int y = graph_height - lifetime_height; y < graph_height; y++) {
            if (x >= 0 && x < graph_width && y >= 0 && y < graph_height) {
                graph[y][x] = '#';
            }
        }
    }
}

for (int y = 0; y < graph_height; y++) {
    printf("%s\n", &graph[y][0]);
}

// Print the instruction count indicators
printf("\nInstruction Count Indicators:\n");
printf("%10d instructions: short program (less than 1 second)\n", total_instructions / 100);
printf("%10d instructions: medium program (1-10 seconds)\n", total_instructions / 10);
printf("%10d instructions: long program (more than 10 seconds)\n", total_instructions);
}

// This is the plugin descriptor
static Panda__Plugin plugin = Panda__Plugin_init_zero;

// This function sets up the plugin
extern "C" Panda__Plugin *init_plugin(void) {
// Set up the plugin descriptor
plugin.api_version = PANDA_PLUGIN_API_VERSION;
plugin.name = (char *)PLUGIN_NAME;
plugin.version = (char *)"1.0";
plugin.plugin_init = init_plugin;
plugin.plugin_fini = uninit_plugin;
plugin.on_translate_block = on_translate;
plugin.on_execute_block = on_execute;
plugin.on_syscall_exit = on_syscall;
plugin.on_bb_end = on_bb_exit;
plugin.on_interrupt = on_interrupt;
plugin.on_replay_end = on_replay_exit;
return &plugin;
}