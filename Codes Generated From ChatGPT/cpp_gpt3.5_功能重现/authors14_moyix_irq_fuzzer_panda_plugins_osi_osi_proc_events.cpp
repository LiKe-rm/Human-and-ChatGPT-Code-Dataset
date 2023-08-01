#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <cstring>
#include <glib.h>

class OsiProcs {
public:
    OsiProcs(const std::set<pid_t>& pids) : pid_set(pids) {}

    std::set<pid_t> pid_set;
};

class ProcState {
public:
    ProcState() {}

    OsiProcs OsiProcsSubset(const std::set<pid_t>& pids) const {
        std::set<pid_t> subset_pids;
        std::map<pid_t, ProcessInfo> subset_proc_map;

        std::set_intersection(pid_set.begin(), pid_set.end(),
                              pids.begin(), pids.end(),
                              std::inserter(subset_pids, subset_pids.begin()));

        for (auto pid : subset_pids) {
            subset_proc_map[pid] = proc_map.at(pid);
        }

        return OsiProcs(subset_pids);
    }

    void update(const std::vector<OsiProcs>& incoming_procs,
                const std::vector<OsiProcs>& outgoing_procs,
                OsiProcs& in,
                OsiProcs& out) {
        // Update pid_set and proc_map with incoming process information
        for (const auto& osi_procs : incoming_procs) {
            for (const auto& pid : osi_procs.pid_set) {
                if (proc_map.count(pid) == 0) {
                    proc_map[pid] = ProcessInfo();
                    pid_set.insert(pid);
                }
                proc_map[pid].incoming = osi_procs;
            }
        }

        // Update pid_set and proc_map with outgoing process information
        for (const auto& osi_procs : outgoing_procs) {
            for (const auto& pid : osi_procs.pid_set) {
                if (proc_map.count(pid) == 0) {
                    proc_map[pid] = ProcessInfo();
                    pid_set.insert(pid);
                }
                proc_map[pid].outgoing = osi_procs;
            }
        }

        // Free old data
        for (auto it = pid_set.begin(); it != pid_set.end(); ) {
            if (proc_map.count(*it) == 0) {
                it = pid_set.erase(it);
            } else {
                ++it;
            }
        }

        // Find incoming and outgoing processes
        std::set<pid_t> incoming_pids;
        std::set<pid_t> outgoing_pids;

        for (const auto& [pid, proc_info] : proc_map) {
            if (proc_info.incoming.pid_set.size() > 0 && proc_info.outgoing.pid_set.size() == 0) {
                incoming_pids.insert(pid);
            } else if (proc_info.incoming.pid_set.size() == 0 && proc_info.outgoing.pid_set.size() > 0) {
                outgoing_pids.insert(pid);
            }
        }

        in = OsiProcsSubset(incoming_pids);
        out = OsiProcsSubset(outgoing_pids);
    }

private:
    struct ProcessInfo {
        OsiProcs incoming;
        OsiProcs outgoing;
    };

    std::set<pid_t> pid_set;
    std::map<pid_t, ProcessInfo> proc_map;
};

ProcState pstate;

void procstate_update(const std::vector<OsiProcs>& incoming_procs,
                      const std::vector<OsiProcs>& outgoing_procs,
                      OsiProcs& in,OsiProcs& out) {
pstate.update(incoming_procs, outgoing_procs, in, out);
}
                     
