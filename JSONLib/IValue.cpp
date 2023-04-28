#include "IValue.h"

namespace JSONLib {
	IValue* IterListValue::Next()
	{
		if (!hasNext()) throw - 1;
		IValue* val = temp->val;
		temp = temp->next;
		return val;
	}

	ListValue::~ListValue()
	{
		while (head != nullptr)
			deleteFirst();
	}

	void ListValue::addFirst(IValue* val)
	{
		Link* link = new Link(val);
		link->next = head;
		if (head != nullptr)
			head->prev = link;
		if (tail == nullptr)
			tail = link;
		head = link;
	}
	void ListValue::addLast(IValue* val)
	{
		Link* link = new Link(val);
		link->prev = tail;
		if (tail != nullptr)
			tail->next = link;
		if (head == nullptr)
			head = link;
		tail = link;
	}
	void ListValue::deleteFirst()
	{
		if (head == nullptr)
			return;
		Link* link = head->next;
		if (link != nullptr)
			link->prev = nullptr;
		else
			tail = nullptr;
		delete head;
		head = link;
	}
	void ListValue::deleteLast()
	{
		if (tail == nullptr)
			return;
		Link* link = tail->prev;
		if (link != nullptr)
			link->next = nullptr;
		else
			head = nullptr;
		delete tail;
		tail = link;
	}
}
