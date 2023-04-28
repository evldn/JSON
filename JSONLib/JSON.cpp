#include "JSON.h"

namespace JSONLib 
{
	void JSON::next() 
	{
		if (!inobj)
		{
			if (jsonitr->hasNext())
			{
				current = jsonitr->Next();
			}
		}
		else
		{
			if (jsonitrin->hasNext())
			{
				current = jsonitrin->Next();
			}
		}
	}
	void JSON::down()
	{
		if (current->getType() == ListVal)
		{
			inobj = true;
			jsonitrin = current->iterator();
			current = jsonitrin->Next();
		}
	}
	void JSON::addFirst(IValue* val)
	{
		root->addFirst(val);
		current = val;
	}
	void JSON::add(IValue* val)
	{
		root->addOnKey(current->getKey(), val);
	}
	void JSON::deleteFirst()
	{
		root->deleteFirst();
		jsonitr = root->iterator();
		current = jsonitr->Next();
	}
	void JSON::del()
	{
		if (current == root)
		{
			deleteFirst();
			return;
		}
		root->delOnKey(current->getKey());

	}
	void JSON::back()
	{
		if (!inobj)
		{
			if (jsonitr->hasPrev())
			{
				current = jsonitr->Prev();
			}
		}
		else
		{
			if (jsonitrin->hasPrev())
			{
				current = jsonitrin->Prev();
			}
		}
	}

	std::string JSON::getJSONString()
	{
		IterIValue* itr = root->iterator();
		std::string s = "";
		while (itr->hasNext())
		{
			IValue* current = itr->Next();
			switch (current->getType())
			{
			case 1:
			{
				if (current->getKey() == getCurrent()->getKey())
				{
					s += "*" + current->getKey() + " : " + current->getValue() + "\n";
				}
				else
				{
					s += current->getKey() + " : " + current->getValue() + "\n";
				}
				break;
			}
			case 2:
			{
				IterIValue* iter = current->iterator();
				if (current->getKey() == getCurrent()->getKey())
				{
					s += "*" + current->getKey() + " : " + "\n";
				}
				else
				{
					s += current->getKey() + " : " + "\n";
				}
				while (iter->hasNext())
				{
					IValue* current_2 = iter->Next();
					if (current_2->getKey() == getCurrent()->getKey())
					{
						s += "    *" + current_2->getKey() + " : " + current_2->getValue() + "\n";
					}
					else
					{
						s += "    " + current_2->getKey() + " : " + current_2->getValue() + "\n";
					}
				}
				break;
			}
			}
		}
		return s;
	}
}