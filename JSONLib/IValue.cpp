#include "IValue.h"

namespace JSONLib {
	void IterListValue::Next()
	{
		temp = temp->next;
	}

	void IterListValue::Prev()
	{
		temp = temp->prev;
	}

	IValue* IterListValue::getTemp()
	{
		return temp->val;
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
		Clear();
	}

	void ListValue::Clear()
	{
		while (head != nullptr)
			deleteFirst();
	}

	bool ListValue::contain(std::string key) {
		for (Link* current = head; current != nullptr; current = current->next) {
			if (current->val->getKey() == key) {
				return true;
			}
		}
		return false;
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
					current->val = newlist;

					/*Link* right = current;
					if (right == nullptr)
						return addLast(newlist);
					Link* left = right->prev;
					if (left == nullptr)
						return addFirst(newlist);
					Link* tmp = new Link(newlist);
					tmp->prev = left;
					tmp->next = right;
					left->next = tmp;
					right->prev = tmp;*/
					break;
				}
				else if (temp->getType() == ListVal)
				{
					static_cast<ListValue*>(temp)->addFirst(val);
					break;
				}
			}
			current = current->next;
		}
	}

	void ListValue::delOnKey(std::string key)
	{
		Link* current = head;
		while (current != nullptr)
		{
			if (current->val->getKey() == key)
			{
				Link* tmp = current;
				if (tmp == nullptr)
					return;
				if (tmp->prev == nullptr)
				{
					deleteFirst();
					return;
				}
				if (tmp->next == nullptr)
				{
					deleteLast();
					return;
				}
				Link* left = tmp->prev;
				Link* right = tmp->next;
				left->next = right;
				right->prev = left;
				delete tmp;
				/*Link* tmp = current;
				current->next->prev = current->prev;
				current->prev->next = current->next;
				if (current->next->next != nullptr)
					current = current->next;
				else if (current->prev != nullptr)
					current = current->prev;
				delete tmp;*/
				break;
			}
			current = current->next;
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
