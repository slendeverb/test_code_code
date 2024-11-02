#include<bits/stdc++.h>
using namespace std;

//空闲分区链的每一个结点，空闲分区链是一个双向链表
struct Node {
    int start;              //开始地址
    int size;               //块大小
    int pid;                //分配给的进程id；
    Node *pre;              //前向指针
    Node *next;             //后向指针
};

//空闲分区表
struct PartitionItem {
    int num;            //分区号
    int size;           //分区大小
    int avaibleMem;     //剩余可用大小
    Node* start;        //起始地址(连接的链表)
    int status;         //分区状态
};

const int N = 5;    //定义5个分区
PartitionItem PARTITIONTABLE[N];        //构建分区表
vector<pair<int, int>> processMap;      //记录已经分配的进程号和区号
int record = -1;     //记录刚刚访问的空闲区区号，用于循环首次适应

//初始化分区表、测试数据
void init() {
    int num = 1;    //分区号
    int size[] = {50, 60, 70, 60, 80};  //各分区大小
    /*初始化时，剩余可用大小avaibleMem = 分区大小
               起始地址start = null
               分区状态status = 0(未分配)
    */
    for (int i = 0; i < N; ++i) {
        PARTITIONTABLE[i].num = num++;
        PARTITIONTABLE[i].size = size[i];
        PARTITIONTABLE[i].avaibleMem = size[i];
        PARTITIONTABLE[i].start = nullptr;
        PARTITIONTABLE[i].status = 0;
    }
}

//将分配的区块(结点)加入链表
void add_to_linklist(int ind, int memory){
    int pid = processMap.back().first;
    Node *node = new Node;
    node->next = nullptr;
    node->pre = nullptr;
    node->pid = pid;
    node->size = memory;
    PARTITIONTABLE[ind].avaibleMem -= memory;
    if(PARTITIONTABLE[ind].start == nullptr) {  //若该区块还是空链表
        node->start = 0;
        PARTITIONTABLE[ind].start = node;
        PARTITIONTABLE[ind].status = 1;
    } else {    //该分区之前已经分配过了，需要遍历到链表尾部进行插入
        Node *p = PARTITIONTABLE[ind].start;
        while(p->next != nullptr) {
            p = p->next;
        }
        p->next = node;
        node->pre = p;
        node->start = p->start + p->size;
    }
}

//遍历进程表，如该进程已经申请，不让继续申请
bool is_pid_exist(int pid) {
    for (int i = 0; i < processMap.size(); ++i) {
        if(pid == processMap[i].first) {
            return true;
        }
    }
    return false;
}

//排序规则
bool cmp(PartitionItem &a, PartitionItem &b) {
    return a.avaibleMem < b.avaibleMem;
}

//首次适应算法，返回值：1--成功；0--失败
int first_fit(int pid, int memory) {
    if(is_pid_exist(pid)){
        cout << "进程已经申请，不要太贪心噢" << endl;
        return 0;
    }
    int flag = 0;           //有无合适分区块标志
    // 遍历分区表，试图寻找一块有适合空闲大小的分区块
    for (int i = 0; i < N; ++i) {
        if(PARTITIONTABLE[i].avaibleMem >= memory) {
            record = i;         //记录下本次访问的区号
            processMap.push_back(make_pair(pid, PARTITIONTABLE[i].num));//记录该进程分配到的区块号
            add_to_linklist(i, memory);
            flag = 1;
            break;
        }
    }
    return flag;
}

//循环首次适应算法，返回值：1--成功；0--失败
int loop_first_fit(int pid, int memory) {
    if(is_pid_exist(pid)){
        cout << "进程已经申请，不要太贪心噢" << endl;
        return 0;
    }
    int flag = 0;           //有无合适分区块标志
    // 从上次访问的下一个区开始遍历分区表，试图寻找一块有适合空闲大小的分区块
    for (int i = (record + 1) % N, k = 1; k <= N; ++k) {
        if(PARTITIONTABLE[i].avaibleMem >= memory) {
            record = i;     //更新record
            processMap.push_back(make_pair(pid, PARTITIONTABLE[i].num));
            add_to_linklist(i, memory);
            flag = 1;
            break;
        }
        i = (i + 1) % N;
    }
    return flag;
}

//最佳适应算法，返回值：1--成功；0--失败
int best_fit(int pid, int memory) {
    //最佳适应算法将所有的分区从小到大排序，寻找第一块有合适大小的进行分配
    if(is_pid_exist(pid)){
        cout << "进程已经申请，不要太贪心噢" << endl;
        return 0;
    }
    int flag = 0;
    //将所有的分区根据剩余可用大小从小到大排序
    sort(PARTITIONTABLE, PARTITIONTABLE + N, cmp);
    // 遍历分区表，试图寻找一块有适合空闲大小的分区块
    for (int i = 0; i < N; ++i) {
        if(PARTITIONTABLE[i].avaibleMem >= memory) {
            record = i;         //记录下本次访问的区号
            processMap.push_back(make_pair(pid, PARTITIONTABLE[i].num));//记录该进程分配到的区块号
            add_to_linklist(i, memory);
            flag = 1;
            break;
        }
    }
    return flag;
}

//回收算法，返回值：1--成功；0--失败
int recycle(int pid) {
    if(!is_pid_exist(pid)) {
        cout << "还没有该进程，不能对它进行回收" << endl;
        return 0;
    }
    int part_num = 0;
    //从processMap中找到该进程分配到的区块号, 同时擦除该记录
    vector<pair<int, int>>::iterator it1 = processMap.begin();
    vector<pair<int, int>>::iterator it2 = processMap.end();
    while(it1 != it2) {
        if((*it1).first == pid) {
            part_num = (*it1).second - 1;
            processMap.erase(it1);
            break;
        }
        it1++;
    }
    //从获取的区块号获得对应的链表
    Node *p = PARTITIONTABLE[part_num].start;
    //遍历链表，找到pid的分块
    while(p != nullptr) {
        if(p->pid == pid) { 
            if(p->pre == nullptr) {     //如果pid的分块是链表的第一个分块，即没有前向块
                PARTITIONTABLE[part_num].start = p->next;
                PARTITIONTABLE[part_num].avaibleMem += p->size;
                if(p->next == nullptr) {    //若后面不再有结点块
                    PARTITIONTABLE[part_num].status = 0;
                } else {
                     p->next->pre = nullptr;     //后面的紧跟块即将成为链表头，其前向指针修改为nullptr
                    //该块后面的其它块资源起始位置前移
                    Node *tmp = p->next;
                    while (tmp != nullptr) {
                        tmp->start -= p->size;
                        tmp = tmp->next;
                    }
                }
            } else {    //结点块处于中间或尾部
                Node *s = p->pre;       //获取前一个结点
                s->next = p->next;
                if(p->next != nullptr) 
                    p->next->pre = s;
                PARTITIONTABLE[part_num].avaibleMem += p->size;
                //该块后面的其它块资源起始位置前移
                Node *tmp = s->next;
                while (tmp != nullptr) {
                    tmp->start = s->start + s->size;
                    tmp = tmp->next;
                }
                delete p;
            }
            break;
        } else {
            p = p->next;
        }
    }
    return 1;
} 

void show_memory() {
    //打印分区表
    printf("分区序号\t分区大小\t可用大小\t分区状态\t\n");
    for (int i = 0; i < N; ++i) {
        printf("%d\t\t%d\t\t%d\t\t", PARTITIONTABLE[i].num, PARTITIONTABLE[i].size, PARTITIONTABLE[i].avaibleMem);
        if (PARTITIONTABLE[i].status == 0)
            printf("空闲\t\t\n");
        else
            printf("已分配\t\t\n");
    }
    //打印分区详情
    for (int i = 0; i < N; ++i) {
        printf("分区号 %d: \n", i + 1);
        Node *p = PARTITIONTABLE[i].start;
        if(p == nullptr) {
            printf("该区暂未分配\n");
        } else {
            int j = 1;
            while(p != nullptr) {
                printf("分块%d: 起始地址  %d\t\t块大小  %d\t\t所属进程号  %d\n", j, p->start, p->size, p->pid);
                p = p->next;
                j++;
            }
        }
    }
}

void menu_print() {
    cout << "1----申请内存" << endl;
    cout << "2----回收内存" << endl;
    cout << "3----内存信息" << endl;
    cout << "0----退出程序" << endl;
    cout << "请输入对应指令的数字: " << endl;
}

int main() {
    init();
    cout << "初始化已完成，请按下列指示输入命令" << endl;
    while(1) {
        int cmd;
        menu_print();
        cin >> cmd;
        if(cmd == 1) {
            int pid, memory, way, res;
            cout << "请输入进程id: " << endl;
            cin >> pid;
            cout << "请输入需要分配的内存大小: " << endl;
            cin >> memory;
            cout << "请选择分配方式: 0--首次适应, 1--循环首次适应, 2--最佳适应" << endl;
            cin >> way;
            if(way != 0 && way != 1 && way != 2)
                cout << "输入有误，回到主菜单" << endl;
            else {
                switch (way)
                {
                    case 0: res = first_fit(pid, memory);
                        break;
                    case 1: res = loop_first_fit(pid, memory);
                        break;
                    case 2: res = best_fit(pid, memory);
                        break;
                }
            }
            if(res)
                cout << "分配成功！" << endl;
            else cout << "分配失败！" << endl;
            cout << endl;
        } else if(cmd == 2) {
            int pid;
            cout << "请输入需要回收的进程号" << endl;
            cin >> pid;
            int res = recycle(pid);
            if(res)
                cout << "回收成功！" << endl;
            else cout << "回收失败！" << endl;
            cout << endl;
        } else if(cmd == 3) {
            show_memory();
            cout << endl;
        } else if(cmd == 0) {
            cout << "退出成功" << endl;
            break;
        } else {
            cout << "输入的指令有误，请重新输入" << endl;
            cin.get();
            continue;
        }
    }
    return 0;
}
