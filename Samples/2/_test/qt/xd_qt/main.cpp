#include "List.h"
#include "RemoveDups.h"
#include "SafeAssert.h"

#include <iostream>
#include <string>
#include <random>
#include <csignal>
/*
Основная логика выполнения первого задания находится в файле RemoveDups.h
Логика выполнения второго задания находится в методах Serialize и Deserialise объекта List,
реализацию которых можно найти в файле List.cpp:41 и List.cpp:75

Для удобства листинг этих методов скопирован сюда:

void List::Serialize(FILE *file)
{
	assert(file);

	// File header with it elements count.
	fprintf(file, "%i\n", Size());

	using umap_t = std::unordered_map<ListNode*, int>;
	umap_t alias_map;

	for(int i = 0; i != count; ++i ){
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

Задачи

1. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке:

("AAA BBB ААА" -> "A B А")

void RemoveDups (char *pStr);

2. Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл.
Алгоритмическая сложность должна быть быстрее квадратичной.

struct ListNode {

ListNode * prev;

ListNode * next;

ListNode * rand; // указатель на произвольный элемент данного списка либо NULL

std::string data;

};

class List {

public:

void Serialize (FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))

void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:

ListNode * head;

ListNode * tail;

int count;

};
*/

void RemoveDuplications() {
	char test_string[] {"AAAAAAAABBBBCCCCCCCCCDDDDDDDEEFFF"};

	std::cout<<"==========\n";
	std::cout<<"Testing <RemoveDups>\nOriginal string is: "<<test_string<<std::endl;

	RemoveDups(test_string);

	std::cout<<"Resulting string is: "<<test_string<<std::endl;
	std::cout<<"==========\n";
}

const char file_path[] = "the_file.txt";
std::string Serialize()
{
	std::random_device generator;
	std::mt19937 mt(generator());
	std::uniform_int_distribution<int> distrib(1, 100);
	int objects_count = distrib(generator);

	List list;
	// Making objects with numerable data.
	while(objects_count--){
		list.PushBack("El_" + std::to_string(objects_count));
	}
	// Making random relations.
	std::uniform_int_distribution<int> sibling(-20, (list.Size()>1) ? list.Size()-1 : 1);
	for(ListNode* element: list){
		int random_object_id = sibling(generator);
		if(random_object_id >= 0)
			element->rand = list.GetElement(random_object_id);
	}

	FILE* file = fopen(file_path, "wb");
	if(file){
		list.Serialize(file);
		fclose(file);
	}

	return list.Dump();
}

std::string Deserialize()
{
	List list;

	FILE* file = fopen(file_path, "rb");
	if(file){
		list.Deserialize(file);
		fclose(file);
	}

	return list.Dump();
}

void AbrtHandler(int)
{
	std::cout<<"Abort signal received!"<<std::endl;
	std::_Exit(EXIT_FAILURE);
}

void SegvHandler(int)
{
	std::cout<<"Segmentation signal received!"<<std::endl;
	std::_Exit(EXIT_FAILURE);
}

void SetAssertHandler()
{
	std::signal(SIGABRT, AbrtHandler);
	std::signal(SIGSEGV, SegvHandler);
}

int main()
{
	SetAssertHandler();
	// Task 1.
	RemoveDuplications();
	// Task 2.
	std::cout<<"Testing Task2 <List>" << std::endl << std::endl;
	std::string serialize_result = Serialize();
	std::cout<<"Result  on  serialization: " << serialize_result << std::endl << std::endl;
	std::string deserialize_result = Deserialize();
	std::cout<<"Result of deserialization: " << deserialize_result << std::endl;
	std::cout<<"==========\n";

	assert(serialize_result == deserialize_result && serialize_result.size());
	std::cout<<"Success!"<<std::endl;

	return 0;
}
