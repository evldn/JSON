#include "JSON.h"

namespace JSONLib 
{
	JSON::JSON()
	{
		root = new ListValue("root", "");
		jsonitr = root->iterator();
		current = nullptr;
	}
	void JSON::next()
	{
		if (!inobj)
		{
			if (jsonitr->hasNext())
			{
				jsonitr->Next();
				current = jsonitr->getTemp();
			}
		}
		else
		{
			if (jsonitrin->hasNext())
			{
				jsonitrin->Next();
				current = jsonitrin->getTemp();
			}
		}
	}
	void JSON::down()
	{
		if (current->getType() == ListVal)
		{
			inobj = true;
			jsonitrin = current->iterator();
			current = jsonitrin->getTemp();
		}
	}

	void JSON::up()
	{
		if (inobj)
		{
			current = jsonitr->getTemp();
			delete jsonitrin;
			inobj = false;
		}
	}

	void JSON::addFirst(IValue* val)
	{
		if (!root->contain(val->getKey()))
		{
			root->addFirst(val);
			jsonitr = root->iterator();
			current = jsonitr->getTemp();
		}
	}
	void JSON::add(IValue* val)
	{
		root->addOnKey(current->getKey(), val);
		jsonitr = root->iterator();
		current = jsonitr->getTemp();
	}
	void JSON::deleteFirst()
	{
		root->deleteFirst();
		jsonitr = root->iterator();
		current = jsonitr->getTemp();
	}
	void JSON::del()
	{
		root->delOnKey(current->getKey());
		jsonitr = root->iterator();
		current = jsonitr->getTemp();
	}
	void JSON::back()
	{
		if (!inobj)
		{
			if (jsonitr->hasPrev())
			{
				jsonitr->Prev();
				current = jsonitr->getTemp();
			}
		}
		else
		{
			if (jsonitrin->hasPrev())
			{
				jsonitrin->Prev();
				current = jsonitrin->getTemp();
			}
		}
	}

	std::string JSON::getJSONString()
	{
		IterIValue* itr = root->iterator();
		std::string s = "";
		while (itr->hasNext())
		{
			IValue* curr = itr->getTemp();
			switch (curr->getType())
			{
			case Val:
			{
				if (curr->getKey() == getCurrent()->getKey())
				{
					s += "*" + curr->getKey() + " : " + curr->getValue() + "\n";
				}
				else
				{
					s += curr->getKey() + " : " + curr->getValue() + "\n";
				}
				break;
			}
			case ListVal:
			{
				IterIValue* iter = curr->iterator();
				if (curr->getKey() == getCurrent()->getKey())
				{
					s += "*" + curr->getKey() + " : " + "\n";
				}
				else
				{
					s += curr->getKey() + " : " + "\n";
				}
				while (iter->hasNext())
				{
					IValue* current_2 = iter->getTemp();
					if (current_2->getKey() == getCurrent()->getKey())
					{
						s += "    *" + current_2->getKey() + " : " + current_2->getValue() + "\n";
					}
					else
					{
						s += "    " + current_2->getKey() + " : " + current_2->getValue() + "\n";
					}
					iter->Next();
				}
				IValue* current_2 = iter->getTemp();
				if (current_2->getKey() == getCurrent()->getKey())
				{
					s += "    *" + current_2->getKey() + " : " + current_2->getValue() + "\n";
				}
				else
				{
					s += "    " + current_2->getKey() + " : " + current_2->getValue() + "\n";
				}
				break;
			}
			}
			itr->Next();
		}
		IValue* curr = itr->getTemp();
		switch (curr->getType())
		{
		case Val:
		{
			if (curr->getKey() == getCurrent()->getKey())
			{
				s += "*" + curr->getKey() + " : " + curr->getValue() + "\n";
			}
			else
			{
				s += curr->getKey() + " : " + curr->getValue() + "\n";
			}
			break;
		}
		case ListVal:
		{
			IterIValue* iter = curr->iterator();
			if (curr->getKey() == getCurrent()->getKey())
			{
				s += "*" + curr->getKey() + " : " + "\n";
			}
			else
			{
				s += curr->getKey() + " : " + "\n";
			}
			while (iter->hasNext())
			{
				IValue* current_2 = iter->getTemp();
				if (current_2->getKey() == getCurrent()->getKey())
				{
					s += "    *" + current_2->getKey() + " : " + current_2->getValue() + "\n";
				}
				else
				{
					s += "    " + current_2->getKey() + " : " + current_2->getValue() + "\n";
				}
				iter->Next();
			}
			IValue* current_2 = iter->getTemp();
			if (current_2->getKey() == getCurrent()->getKey())
			{
				s += "    *" + current_2->getKey() + " : " + current_2->getValue() + "\n";
			}
			else
			{
				s += "    " + current_2->getKey() + " : " + current_2->getValue() + "\n";
			}
			break;
		}
		}
		return s;
	}
}