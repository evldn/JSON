#pragma once

#include <string>

namespace JSONLib
{
	class IterIValue;

	enum TypeValue {
		Val,
		ListVal
	};

	class IValue {
	public:
		virtual TypeValue getType() = 0;
		virtual std::string getKey() = 0;
		virtual std::string getValue() = 0;
		virtual IterIValue* iterator() = 0;
	};

	struct Link {
		Link* next;
		Link* prev;
		IValue* val;
	public:
		Link(IValue* _val, Link* _next = nullptr, Link* _prev = nullptr) : next(_next), prev(_prev), val(_val) { }
	};

	class IterIValue {
	public:
		virtual bool hasNext() = 0;
		virtual void Next() = 0;
		virtual bool hasPrev() = 0;
		virtual void Prev() = 0;
		virtual IValue* getTemp() = 0;
	};

	class IterValue : public IterIValue {
		IValue* val;
	public:
		IterValue(IValue* _val) : val(_val) { }
		bool hasNext() { return false; }
		void Next() { return; }
		bool hasPrev() { return false; }
		void Prev() { return; }
		IValue* getTemp() { return val; }
	};

	class IterListValue : public IterIValue {
		Link* temp;
		Link* tail;
	public:
		IterListValue(Link* head, Link* _tail) : temp(head), tail(_tail) { }
		bool hasNext() { return temp->next != nullptr; }
		void Next();
		bool hasPrev() { return temp->prev != nullptr; }
		void Prev();
		IValue* getTemp();
	};

	class Value :public IValue {
		std::string key;
		std::string val;
	public:
		Value(std::string _key, std::string _val) : key(_key), val(_val) { }
		Value(Value* val);
		TypeValue getType() { return Val; }
		std::string getKey() { return key; }
		std::string getValue() { return val; }
		IterIValue* iterator() { return new IterValue(this); }
	};

	class ListValue :public IValue {
		std::string key;
		std::string value;
		Link* head;
		Link* tail;
	public:
		ListValue(std::string _key, std::string _value) : key(_key), value(_value), head(nullptr), tail(nullptr) { }
		ListValue(ListValue* list);
		~ListValue();
		void Clear();
		TypeValue getType() { return ListVal; }
		std::string getKey() { return key; }
		std::string getValue() { return value; }
		IterIValue* iterator() { return new IterListValue(head, tail); }
		bool contain(std::string key);
		void addFirst(IValue* val);
		void addLast(IValue* val);
		void addOnKey(std::string key, IValue* val);
		void delOnKey(std::string key);
		void deleteFirst();
		void deleteLast();
		bool isEmpty() { return head == nullptr; }
	};
}