#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <optional>
#include <string>

const int PageSize = 1024;

struct Page {
    int id;
    int frameNum;
    bool inMemory;
    int accessField;
    bool modified;
    int storageAddress;
    int processID;
};

struct PageTable {
    std::vector<Page> pages;

    PageTable(int numPages, int processID) {
        for (int i = 0; i < numPages; ++i) {
            pages.push_back({i, -1, false, 0, false, -1, processID});
        }
    }
};

struct Frame {
    int id;
    int processID;
    bool allocated;
};

class Memory {
private:
    std::vector<Frame> frames;
    std::queue<int> freeFrames;
    std::unordered_map<int, int> frameMap; // pageID -> frameID

public:
    Memory(int totalFrames) {
        for (int i = 0; i < totalFrames; ++i) {
            frames.push_back({i, -1, false});
            freeFrames.push(i);
        }
    }

    bool hasFreeFrame() const { return !freeFrames.empty(); }

    std::optional<int> allocateFrame(int processID) {
        if (freeFrames.empty()) {
            return std::nullopt;
        }
        int frameID = freeFrames.front();
        freeFrames.pop();
        frames[frameID].allocated = true;
        frames[frameID].processID = processID;
        return frameID;
    }

    void deallocateFrame(int frameID) {
        if (frameID < 0 || frameID >= frames.size()) {
            std::cerr << "Invalid frame ID for deallocation: " << frameID << "\n";
            return;
        }
        frames[frameID].allocated = false;
        frames[frameID].processID = -1;
        freeFrames.push(frameID);
    }

    void printFrames() const {
        std::cout << "Frames:\n";
        for (const auto& frame : frames) {
            std::cout << "Frame ID: " << frame.id << ", Allocated: " << frame.allocated
                      << ", Process ID: " << frame.processID << "\n";
        }
    }
};

class Process {
private:
    int id;
    PageTable pageTable;
    Memory& memory;

public:
    Process(int processID, int memoryNeed, Memory& mem)
        : id(processID), pageTable(ceil(static_cast<double>(memoryNeed) / PageSize), processID), memory(mem) {}

    void accessPage(int pageID) {
        if (pageID < 0 || pageID >= pageTable.pages.size()) {
            std::cerr << "Invalid page ID: " << pageID << "\n";
            return;
        }

        Page& page = pageTable.pages[pageID];
        if (page.inMemory) {
            std::cout << "Page " << pageID << " is in memory (Frame: " << page.frameNum << ").\n";
            page.accessField++;
        } else {
            std::cout << "Page " << pageID << " is not in memory. Allocating...\n";
            auto frameOpt = memory.allocateFrame(id);
            if (!frameOpt.has_value()) {
                std::cerr << "No free frames available! Page swap needed.\n";
                return;
            }
            page.inMemory = true;
            page.frameNum = frameOpt.value();
            std::cout << "Page " << pageID << " loaded into Frame " << page.frameNum << ".\n";
        }
    }

    void printPageTable() const {
        std::cout << "Page Table for Process " << id << ":\n";
        for (const auto& page : pageTable.pages) {
            std::cout << "Page ID: " << page.id
                      << ", Frame: " << (page.inMemory ? std::to_string(page.frameNum) : "Not in Memory")
                      << ", Access Field: " << page.accessField << "\n";
        }
    }
};

int main() {
    int memorySize = 16 * PageSize;
    int totalFrames = memorySize / PageSize;

    Memory memory(totalFrames);

    Process process1(1, 5 * PageSize, memory);
    process1.accessPage(0);
    process1.accessPage(1);
    process1.accessPage(2);
    process1.accessPage(3);
    process1.accessPage(4);

    process1.printPageTable();
    memory.printFrames();
    return 0;
}