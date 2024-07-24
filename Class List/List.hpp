#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <iostream>
#include <initializer_list>
#include <exception>


template <typename ANY>
class List {

private:
	struct Item {
		ANY value = ANY();// = ANY() - конструктор по умолчанию // или {}
		Item* next = nullptr;
		Item* prev = nullptr;
		Item(ANY value) : value(value) {} //конструктор
	};
	Item* first;
	Item* last;
	size_t length;//size_t _size можно так
	void set_defaults();

public:
	List(); // конструктор по умолчанию
	List(const std::initializer_list<ANY>& inits);
	~List();// деструктор

	void print() const;
	void reverse_print() const;

	void push_back(ANY value);
	void push_front(ANY value);
	void pop_back();
	void pop_front();
	void clear();

	size_t size() const;
	ANY& front();
	const ANY& front() const;
	ANY& back();
	const ANY& back() const;
};

template<typename ANY>
void List<ANY>::set_defaults() {
	first = nullptr;
	last  = nullptr;
	length = 0;
}

template<typename ANY>
List<ANY>::List() { set_defaults(); }

template<typename ANY>
List<ANY>::List(const std::initializer_list<ANY>& inits) {
	set_defaults();
	for (auto el : inits)
		push_back(el);
}

template<typename ANY>
List<ANY>::~List() { clear();}

template<typename ANY>
void List<ANY>::print() const {
	if (first == nullptr) {
		std::cout << '\n';
		return;
	}

	Item* curret = first;
	do {
	std::cout << curret->value << ' ';
	curret = curret->next;
	} while (curret != nullptr);
	std::cout << std::endl;
}

template<typename ANY>
 void List<ANY>::reverse_print() const {
	 if (last == nullptr) {
		 std::cout << '\n';
		 return;
	 }

	 Item* curret = last;
	 do {
		 std::cout << curret->value << ' ';
		 curret = curret->prev;
	 } while (curret != nullptr);
	 std::cout << std::endl;
}

template<typename ANY>
 void List<ANY>::push_back(ANY value) {

	 if (last == nullptr) {
		 last = first = new Item(value); //last = first;  1 вариант
		 ++length;
		 return;
	 }

	 last->next = new Item(value);
	 last->next->prev = last;
	 last = last->next;
	 ++length;
}

template<typename ANY>
 void List<ANY>::push_front(ANY value) {
	 if (first == nullptr) { // если нет элементов в списке
		 first = last = new Item(value); 
		 ++length;
		 return;
	 }

	 first->prev = new Item(value);
	 first->prev->next = first;
	 first = first->prev;
	 ++length;
}

template<typename ANY>
 void List<ANY>::pop_back() {
	 if (last == nullptr)
		 throw std::exception(" list have no elements");

	 if (first == last) {
		 delete last;
		 set_defaults();
		 return;
	 }

	 last = last->prev;
	 delete last->next;
	 last->next = nullptr;
	 --length;

}

template<typename ANY>
 void List<ANY>::pop_front() {
	 if (first == nullptr)
		 throw std::exception(" list have no elements");

	 if (first == last) {
		 delete first;
		 set_defaults();
		 return;
	 }

	 first = first->next;
	 delete first->prev;
	 first->prev = nullptr;
	 --length;
}

 template<typename ANY>
 void List<ANY>::clear() {
	 if (first == nullptr)
		 return;

	 Item* current = first;
	 do {
		 Item* to_delete = current;
		 current = current->next;
		 delete to_delete;
	 } while (current != nullptr);

	 set_defaults();
 }

template<typename ANY>
 size_t List<ANY>::size() const {
	return length;
}

 template<typename ANY>
 ANY& List<ANY>::front() {
	 return first->value;
 }

 template<typename ANY>
 const ANY& List<ANY>::front() const {
	 return first->value;
 }

 template<typename ANY>
 ANY& List<ANY>::back() {
	 return last->value;
 }

 template<typename ANY>
 const ANY& List<ANY>::back() const {
	 return last->value;
 }


#endif// _LIST_HPP_