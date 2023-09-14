#include <iostream>

class LinkList
{
public:
    LinkList(int n) : size(n)
    {
        createLinkList(size);
    }
    ~LinkList()
    {
        deleteLinkList();
    }

    void reverseLinkList();
    void printLinkList();

private:
    typedef int Datatype;

    struct ListNode
    {
        Datatype Data;
        ListNode *next;

        ListNode()
        {
            next = nullptr;
        }
    };

    ListNode *head = nullptr;
    int size;

    void createLinkList(int size);
    void deleteLinkList();
};

void LinkList::createLinkList(int size)
{
    head = new ListNode;
    head->next = nullptr;

    ListNode *pos = nullptr, *prev = head;

    for (int i = 1; i <= size; i++)
    {
        pos = new ListNode;
        std::cin >> pos->Data;
        prev->next = pos;
        prev = pos;
    }
}

void LinkList::deleteLinkList()
{
    ListNode *pos = head->next;
    while (pos != nullptr)
    {
        head->next = pos->next;
        delete pos;
        pos = pos->next;
    }
    delete head;
}

void LinkList::reverseLinkList()
{
    if (size == 1)
    {
        return;
    }

    ListNode *prev = nullptr, *pos = head->next, *next = head->next->next;

    while (next != nullptr)
    {
        pos->next = prev;
        prev = pos;
        pos = next;
        next = next->next;
    }

    pos->next = prev;
    head->next = pos;
}

void LinkList::printLinkList()
{
    ListNode *pos = head->next;

    if (size == 0)
    {
        std::cout << "LinkList is empty!\n";
        return;
    }

    while (pos != nullptr)
    {
        std::cout << pos->Data << " ";
        pos = pos->next;
    }

    std::cout << std::endl;
}

int main()
{
    int n;
    std::cin >> n;
    LinkList L(n);
    L.printLinkList();
    L.reverseLinkList();
    L.printLinkList();
    return 0;
}