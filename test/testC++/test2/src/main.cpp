#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int globalTime = 0; // Global time for LRU

struct PageFrame {
    int frameNumber;
    int lastUsedTime; // For LRU
};

struct PageFrameManager {
    list<PageFrame> frames; // For FIFO
    unordered_map<int, list<PageFrame>::iterator> frameMap; // For LRU and FIFO
    int capacity;

    PageFrameManager(int cap) : capacity(cap) {}

    void accessPage(int pageNumber, bool isFIFO) {
        if (frameMap.find(pageNumber) != frameMap.end()) {
            if (!isFIFO) { // Update lastUsedTime for LRU
                PageFrame& page = *frameMap[pageNumber];
                page.lastUsedTime = ++globalTime;
            }
            return;
        }

        if (frames.size() < capacity) {
            // Add new frame
            PageFrame newFrame = {pageNumber, isFIFO ? 0 : ++globalTime};
            frames.push_back(newFrame);
            frameMap[pageNumber] = --frames.end();
        } else {
            // Replace frame
            if (isFIFO) {
                // FIFO replacement
                frameMap.erase(frames.front().frameNumber);
                frames.pop_front();
            } else {
                // LRU replacement
                auto it = frames.begin();
                auto lruIt = it;
                for (auto& frameIt : frames) {
                    if (frameIt.lastUsedTime < lruIt->lastUsedTime) {
                        *lruIt = frameIt;
                    }
                }
                frameMap.erase(lruIt->frameNumber);
                frames.erase(--frames.end());
            }

            // Add new frame
            PageFrame newFrame = {pageNumber, isFIFO ? 0 : ++globalTime};
            frames.push_back(newFrame);
            frameMap[pageNumber] = --frames.end();
        }
    }

    void printFrames(bool isFIFO) {
        cout << (isFIFO ? "FIFO: " : "LRU: ");
        for (const auto& frame : frames) {
            cout << frame.frameNumber << " ";
        }
        cout << endl;
    }
};

int main() {
    vector<int> pageAccessSequence = {4, 7, 0, 7, 1, 0, 1, 2, 1, 2, 6};
    int numPhysicalFrames = 5;

    // FIFO
    cout << "FIFO Page Replacement:" << endl;
    PageFrameManager fifoManager(numPhysicalFrames);
    for (int pageNumber : pageAccessSequence) {
        fifoManager.accessPage(pageNumber, true);
        fifoManager.printFrames(true);
    }

    // Reset global time and frame map for LRU
    globalTime = 0;
    PageFrameManager lruManager(numPhysicalFrames);

    // LRU
    cout << "LRU Page Replacement:" << endl;
    for (int pageNumber : pageAccessSequence) {
        lruManager.accessPage(pageNumber, false);
        lruManager.printFrames(false);
    }

    return 0;
}