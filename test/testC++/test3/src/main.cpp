#include <iostream>
#include <map>
#include <unordered_map>
#include <numeric>
#include <queue>
#include <cassert>
#include <optional>

const int PageSize=1024;

struct Page{
	int id;
	int frameNum;
	bool inMemory;
	int accessField;
	bool modified;
	int storageAddress;
};

struct PageTableRegister{
    int startAddress{0};
    int length{0};
}ptr;

struct TLB{
    int TLB_size{16};
    std::unordered_map<int,Page*> TLB;
}tlb;

struct StorageArea{
	int startAddress;
	int size;
};

struct SwapArea:public StorageArea{};
struct FileArea:public StorageArea{};

struct Node{
	int processId;
	int size;
	int startAddress;
};

struct Storage{
	SwapArea swapArea;
	FileArea fileArea;
	std::vector<int> nodeSize;
	std::vector<std::vector<Node>> freeNodes;

	Storage(int swapAreaSize,int fileAreaSize){
		swapArea.startAddress=0;
		swapArea.size=swapAreaSize;
		int idx=0;
		for(int i=1;i<=swapAreaSize;i<<=1){
			nodeSize.push_back(i);
			idx++;
		}
		freeNodes.resize(idx+1);
		freeNodes[idx].emplace_back(-1,swapAreaSize,0);

		fileArea.startAddress=swapAreaSize;
		fileArea.size=fileAreaSize;
	}

	std::optional<int> alloc(int processId,int allocSize){
		int idx=std::lower_bound(nodeSize.begin(),nodeSize.end(),allocSize)-nodeSize.begin();
		if(!freeNodes[idx].empty()){
			for(Node node:freeNodes[idx]){
				if(node.processId!=-1){
					continue;
				}
				node.processId=processId;
				return node.startAddress;
			}
		}
		for(int i=idx+1;i<freeNodes.size();i++){
			if(freeNodes[i].empty()){
				continue;
			}
			int k=i;
			int minSize=nodeSize[k];
			while(minSize>nodeSize[idx]){
				for(int j=0;j<freeNodes[k].size();j++){
					Node node=freeNodes[k][j];
					if(node.processId!=-1){
						continue;
					}
					int xNodeSize=node.size>>1;
					Node x1{-1,xNodeSize,node.startAddress};
					Node x2{-1,xNodeSize,node.startAddress+xNodeSize};
					freeNodes[k].erase(freeNodes[k].begin()+j);
					freeNodes[k-1].push_back(x1);
					freeNodes[k-1].push_back(x2);
					break;
				}
				k--;
				minSize>>=1;
			}
			for(Node node:freeNodes[k]){
				if(node.processId!=-1){
					continue;
				}
				node.processId=processId;
				return node.startAddress;
			}
		}
		return std::nullopt;
	}

	void recycle(int address){
		for(int i=0;i<freeNodes.size();i++){
			if(freeNodes[i].empty()){
				continue;
			}
			for(int j=0;j<freeNodes[i].size();j++){
				if(freeNodes[i][j].startAddress==address){
					freeNodes[i][j].processId=-1;
				}
			}
			std::vector<int> removeList;
			bool allFree=false;
			int nodeSizeK=-1;
			int buddyAddress=-1;
			for(int j=0;j<freeNodes[i].size();j++){
				Node node=freeNodes[i][j];
				if(node.processId!=-1){
					continue;
				}
				removeList.push_back(j);
				nodeSizeK=node.size;
				buddyAddress=isPowerOfTwo(address)?address+nodeSizeK:address-nodeSizeK;
				for(int k=0;k<freeNodes[i].size();k++){
					Node node=freeNodes[i][j];
					if(node.startAddress!=buddyAddress || node.processId!=-1){
						continue;
					}
					allFree=true;
					removeList.push_back(k);
					break;
				}
			}
			if(!allFree){
				continue;
			}
			for(int j=0;j<removeList.size();j++){
				freeNodes[i].erase(freeNodes[i].begin()+removeList[j]);
			}
			freeNodes[i+1].emplace_back(Node{-1,nodeSizeK<<1,isPowerOfTwo(address)?address:buddyAddress});
		}
	}

	bool isPowerOfTwo(int x){
		return x>0 && (x&(x-1))==0;
	}
}storage{4096*PageSize,16*1024*PageSize};

struct Frame{
	int id;
	int length;
	bool isAlloc;
	int startAddress;
};

struct Memory{
	std::vector<Frame> frames;
	std::priority_queue<Frame*,std::vector<Frame*>,cmp> freeFrames;
	std::unordered_map<int,Frame*> allocedFrames;

	Memory(int memorySize){
		frames.resize(memorySize/PageSize);
		for(int i=0;i<frames.size();i++){
			frames[i].id=i;
			frames[i].isAlloc=false;
			frames[i].length=PageSize;
			frames[i].startAddress=i>0?frames[i-1].startAddress+frames[i-1].length:0;
		}
		for(int i=0;i<frames.size();i++){
			if(frames[i].isAlloc){
				allocedFrames[frames[i].id]=&frames[i];
				continue;
			}
			freeFrames.push(&frames[i]);
		}
	}

	bool hasFree(){
		return !freeFrames.empty();
	}

	int alloc(){
		Frame* framePtr=freeFrames.top();
		freeFrames.pop();
		framePtr->isAlloc=true;
		allocedFrames[framePtr->id]=framePtr;
		return framePtr->id;
	}

	void recycle(int id){
		Frame* framePtr=allocedFrames[id];
		allocedFrames.erase(id);
		freeFrames.push(framePtr);
	}
}memory{4096*PageSize};

struct cmp{
    bool operator()(const Frame* a,const Frame* b){
        return a->id>b->id;
    }
};

struct PageTable{
	inline static int MinPageNum=6;
	std::vector<Page> pages;

	PageTable(int memoryNeed){
		int pageNum=(int)ceil((double)memoryNeed/PageSize);
		for(int i=0;i<pageNum;i++){
			if(i<MinPageNum && memory.hasFree()){
				int frameNum=memory.alloc();
				pages.emplace_back(i,frameNum,true,0,false,-1);
			}else{
				try{
					std::optional<int> storageAddress=storage.alloc(i,PageSize);
					if(!storageAddress.has_value()){
						throw std::exception{"Swap Area is full."};
					}
					pages.emplace_back(i,-1,false,0,false,storageAddress.value());
				}catch(std::exception& e){
					std::cerr<<e.what()<<"\n";
				}
			}
		}
		int minSize=std::min(pageNum,tlb.TLB_size);
		for(int i=0;i<minSize;i++){
			tlb.TLB[pages[i].id]=&pages[i];
		}
	}
};

struct Process{
    int memoryNeed;
    PageTable pageTable;
    
    Process(int memoryNeed)
		:memoryNeed{memoryNeed},
		pageTable{memoryNeed}{
        
    }
    ~Process(){
        
    }
};

void accessMemory(Process& process,int A){
    int P=A/PageSize,d=A%PageSize;
    if(tlb.TLB.count(P)){
        std::cout<<"Physical Address of Logical Address A is (from TLB):\n";
        
    }else{
        std::cout<<"Physical Address of Logical Address A is (from PT):\n";
        
    }
}

int main(int argc, char** argv) {
    Process process{20*PageSize};
    std::cout<<"Memory Frame Number:\n";
    for(int i=0;i<process.memoryNeed;i++){
		
    }
    std::cout<<"\n";
    int A=5*PageSize+28;
    assert(A<process.memoryNeed*PageSize);
    accessMemory(process,A);
    A=18*PageSize+90;
    accessMemory(process,A);
}