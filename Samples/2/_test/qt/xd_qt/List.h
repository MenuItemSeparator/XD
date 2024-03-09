#pragma once

#include <string>
#include <iterator>
#include <cassert>

// @Brief: Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл.
// Алгоритмическая сложность должна быть быстрее квадратичной.
struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка либо NULL
    std::string data;
public:
    ListNode(std::string&) = delete;
    ListNode(std::string&& _value)
    {
        data = _value;
        prev = next = rand = nullptr;
    }
};

class List {
public:
    // Simple forward iterator for ranged cycles.
    class iterator //: public std::iterator // Not needed.
    {
        ListNode* node;
    public:
        iterator(ListNode* _node): node(_node) {}
        iterator operator ++ () { node = node->next; return node; }
        ListNode* operator * () { return node; }
        bool operator != (iterator _value) { return node != *_value; }
    };

    List();
    ~List()
    {
        if(count){
            assert(head && "Count more than one but head is zero");
            while(head){
                ListNode* ptr = head;
                head = head->next;
                delete ptr;
            }
        }
    }

    void Serialize (FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

    // Creates and insert new NodeElement by string.
    void PushBack(std::string _value);
    int Size() const {return count;}
    // Returns human readable representation of the List.
    std::string Dump() const;
    ListNode* GetElement(int _num);

    iterator begin() {return head;}
    iterator end() {return tail;}

private:
    void Insert(ListNode* _value);
    ListNode* MakeElement(std::string _value);

private:
    ListNode* head;
    ListNode* tail;
    int count;
};


