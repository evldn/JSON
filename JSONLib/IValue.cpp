#include "IValue.h"

namespace JSONLib {
	IValue* IterListValue::Next()
	{
		if (!hasNext()) throw - 1;
		IValue* val = temp->val;
		temp = temp->next;
		return val;
	}

	IValue* IterListValue::Prev()
	{
		if (!hasPrev()) throw - 1;
		IValue* val = temp->val;
		temp = temp->prev;
		return val;
	}
	

	ListValue::ListValue(ListValue* list)
	{
		key = list->key;
		value = list->value;
		head = nullptr;
		tail = nullptr;
		Link* current = list->head;
		while (current != nullptr)
		{
			addLast(current->val);
			current = current->next;
		}
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
	void ListValue::addOnKey(std::string key, IValue* val)
	{
		IValue* temp;
		Link* current = head;
		while (current != nullptr)
		{
			temp = current->val;
			if (temp->getKey() == key)
			{
				if (temp->getType() == Val)
				{
					ListValue* newlist = new ListValue(temp->getKey(), "");
					newlist->addFirst(temp);
					newlist->addFirst(val);
					Link* tmp = current;
					current = new Link(newlist, tmp->next, tmp->prev);
					delete tmp;
				}
				else if (temp->getType() == ListVal)
				{
					static_cast<ListValue*>(temp)->addFirst(val);
				}
			}
			current = current->next;
		}
	}

	void ListValue::delOnKey(std::string key)
	{
		IValue* temp;
		Link* current = head;
		while (current != nullptr)
		{
			temp = current->val;
			if (temp->getKey() == key)
			{
				Link* tmp = current;
				current->next->prev = current->prev;
				current->prev->next = current->next;
				if (current->next->next != nullptr)
					current = current->next;
				else if (current->prev != nullptr)
					current = current->prev;
				delete tmp;
			}

		}
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
	Value::Value(Value* value)
	{
		key = value->key;
		val = value->val;
	}
}
