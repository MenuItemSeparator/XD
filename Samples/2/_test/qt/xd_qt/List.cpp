#include "List.h"

#include <climits>
#include <unordered_map>
#include <vector>
#include <cstring>

List::List(): head(nullptr), tail(nullptr), count(0)
{
    // Initial tail element.
    tail = MakeElement("");
}

ListNode* List::MakeElement(std::string _value)
{
    return new ListNode(std::move(_value));
}

void List::PushBack(std::string _value)
{
    assert(count != INT_MAX && tail);

    ListNode* node = MakeElement(_value);
    Insert(node);
}

void List::Insert(ListNode *_value)
{
    assert(_value);
    if(count++){
        tail->prev->next = _value;
        _value->prev = tail->prev;
        _value->next = tail;
        tail->prev = _value;
    }
    else{
        tail->prev = head = _value;
    }
}

void List::Serialize(FILE *file)
{
    assert(file);

    // File header with it elements count.
    fprintf(file, "%i\n", Size());

    using umap_t = std::unordered_map<ListNode*, int>;
    umap_t alias_map;

    for(/*size_t*/int i = 0; i != count; ++i ){
        ListNode* element = GetElement(i);
        assert(element);
        // I need block size before each block.
        fprintf(file, "%s\n", element->data.c_str());

        //Save alias and order in file.
        alias_map.insert(umap_t::value_type(element, i));
    }
    // Save elements relations.
    for(ListNode* element: *this){
        assert(element);
        if(element->rand){
            int i = alias_map.find(element->rand)->second;
            fprintf(file, "%i\n", i);
        }
        else{
            fprintf(file, "null\n");
        }
    }
    // Last control symbol.
    fprintf(file, ";");
}

void List::Deserialize(FILE *file)
{
    assert(file);
    // Dynamic container will be better(std::list<byte>), but for the simple task used simple array.
    const int buffsize = 500;
    char buff[buffsize];
    // Reading header with objects count.
    fgets(buff, buffsize, file);
    int element_count = atoi(buff);
    // Ptr order container.
    std::vector<ListNode*> nodes_order(static_cast<size_t>(element_count));
    // Reading objects data.
    for(int i = 0; i < element_count; i++)
    {
        fgets(buff, buffsize, file);
        size_t end_of_str = strlen(buff);
        buff[(end_of_str > 1)? end_of_str - 1 : 0] = '\0';
        ListNode* element = MakeElement(buff);
        Insert(element);
        nodes_order[static_cast<size_t>(i)] = element;
    }
    // Reading objects relations.
    for(int i = 0; i < element_count; i++){
        fgets(buff, buffsize, file);
        // Prevent NULL relation.
        if(strcmp(buff, "null\n"))
            nodes_order[static_cast<size_t>(i)]->rand = nodes_order[static_cast<size_t>(atoi(buff))];
    }
    // Reading and check control symbol.
    fgets(buff, buffsize, file);
    assert(buff[0] == ';');
}

std::string List::Dump() const
{
    if(!count){
        return std::string {"List is empty"};
    }
    std::string dump("Elements count: " + std::to_string(count) + ";");
    for(const ListNode* element = head; element != tail; element = element->next){
        assert(element);
        dump += "Element " + element->data + ':';
        dump += "Looking for " + ((element->rand != nullptr) ? element->rand->data : "none");
        dump += ";";
    }
    return dump;
}

ListNode* List::GetElement(int _num)
{
    assert(_num < count);

    ListNode *ptr = head;
    for(; _num != 0; ptr = ptr->next, _num--){
        assert(ptr != nullptr);
    }
    return ptr;
}
