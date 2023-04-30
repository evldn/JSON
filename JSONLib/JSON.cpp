#include "JSON.h"
#include <fstream>
#include <iostream>
#include <string>

namespace JSONLib 
{
	JSON::JSON()
	{
		root = new ListValue("root", "");
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
			if (inobj)
			{
				inobj = false;
				delete jsonitrin;
			}
		}
	}
	void JSON::add(IValue* val)
	{
		if (inobj)
		{
			root->addOnKey(jsonitr->getTemp()->getKey(), val);
			jsonitrin = jsonitr->getTemp()->iterator();
			current = jsonitrin->getTemp();
		}
		else
		{
			root->addOnKey(current->getKey(), val);
			jsonitr = root->iterator();
			current = jsonitr->getTemp();
		}
		
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
		str = "{\n";
		std::string colomn = "\"";
		while (itr->hasNext())
		{
			str += "    ";
			IValue* curr = itr->getTemp();
			switch (curr->getType())
			{
			case Val:
			{
				if (curr->getKey() == getCurrent()->getKey())
				{
					str += "*" + colomn + curr->getKey() + colomn + " : " + colomn + curr->getValue() + colomn + "\n";
				}
				else
				{
					str += colomn + curr->getKey() + colomn + " : " + colomn + curr->getValue() + colomn + "\n";
				}
				break;
			}
			case ListVal:
			{
				IterIValue* iter = curr->iterator();
				if (curr->getKey() == getCurrent()->getKey())
				{
					str += "*" + colomn + curr->getKey() + colomn + " : " + "\n";
				}
				else
				{
					str += colomn + curr->getKey() + colomn + " : " + "\n";
				}
				str += "    {\n";
				while (iter->hasNext())
				{
					IValue* current_2 = iter->getTemp();
					if (current_2->getKey() == getCurrent()->getKey())
					{
						str += "        *" + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
					}
					else
					{
						str += "        " + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
					}
					iter->Next();
				}
				IValue* current_2 = iter->getTemp();
				if (current_2->getKey() == getCurrent()->getKey())
				{
					str += "        *" + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
				}
				else
				{
					str += "        " + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
				}
				str += "    }\n";
				break;
			}
			}
			itr->Next();
		}
		str += "    ";
		IValue* curr = itr->getTemp();
		switch (curr->getType())
		{
		case Val:
		{
			if (curr->getKey() == getCurrent()->getKey())
			{
				str += "*" + colomn + curr->getKey() + colomn + " : " + colomn + curr->getValue() + colomn + "\n";
			}
			else
			{
				str += colomn + curr->getKey() + colomn + " : " + colomn + curr->getValue() + colomn + "\n";
			}
			break;
		}
		case ListVal:
		{
			IterIValue* iter = curr->iterator();
			if (curr->getKey() == getCurrent()->getKey())
			{
				str += "*" + colomn + curr->getKey() + colomn + " : " + "\n";
			}
			else
			{
				str += colomn + curr->getKey() + colomn + " : " + "\n";
			}
			str += "    {\n";
			while (iter->hasNext())
			{
				IValue* current_2 = iter->getTemp();
				if (current_2->getKey() == getCurrent()->getKey())
				{
					str += "        *" + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
				}
				else
				{
					str += "        " + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
				}
				iter->Next();
			}
			IValue* current_2 = iter->getTemp();
			if (current_2->getKey() == getCurrent()->getKey())
			{
				str += "        *" + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
			}
			else
			{
				str += "        " + colomn + current_2->getKey() + colomn + " : " + colomn + current_2->getValue() + colomn + "\n";
			}
			str += "    }\n";
			break;
		}
		}
		return str + "}";
	}

	void JSON::load(std::string file_name)
	{
		root->Clear();
		std::ifstream f_in(file_name);
		std::string tmp = "";
		str = "";
		while (!f_in.eof())
		{
			f_in >> tmp;
			str += tmp;
		}
		parse(str, root);
		jsonitr = root->iterator();
		current = jsonitr->getTemp();
	}

	void JSON::parse(std::string input, ListValue* obj)
	{
		std::string key = "";
		std::string value = "";
		std::string tmp = "";
		std::string sep = " \n\t";
		int prev_state = -1;
		int state = 0;
		for (int i = 0; i < input.size(); i++)
		{
			char c = input[i];
			int fres = sep.find(c);
			if (fres >= 0)
				continue;
			switch (state)
			{
			case 0: //открывающаяся скобка
			{
				if ((c == '{') && (prev_state == -1))
				{
					prev_state = state;
					state = 1;
					break;
				}
			}
			case 1: //ключ
			{
				if ((c == '"') && ((prev_state == 0) || (prev_state == 4) || (prev_state == 6)))
				{
					tmp = "";
					prev_state = state;
					state = 1;
					break;
				}
				if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				{
					tmp += c;
					prev_state = state;
					state = 1;
					break;
				}
				if ((c == '"') && (prev_state == 1))
				{
					key = tmp;
					prev_state = state;
					state = 2;
					break;
				}
			}
			case 2: //двоеточие
			{
				if ((c == ':') && (prev_state == 1))
				{
					prev_state = state;
					state = 3;
					break;
				}
			}
			case 3: // значение
			{
				if ((c == '"') && (prev_state == 2))
				{
					tmp = "";
					prev_state = state;
					state = 3;
					break;
				}
				if ((c != '"') && (prev_state == 3))
				{
					tmp += c;
					prev_state = state;
					state = 3;
					break;
				}
				if ((c == '"') && (prev_state == 3))
				{
					value = tmp;
					prev_state = state;
					state = 4;
					break;
				}
				if ((c == '{') && (prev_state == 2))
				{
					tmp = c;
					prev_state = state;
					state = 5;
					break;
				}
			}
			case 4: //запятая
			{
				obj->addLast(new Value(key, value));
				if (c == ',' && prev_state == 3)
				{
					prev_state = state;
					state = 1;
					break;
				}
				if (c == '}' && prev_state == 3)
				{
					prev_state = -1;
					state = 0;
					break;
				}
			}
			case 5: //объект
			{
				if ((c == '"') && (prev_state == 3))
				{
					tmp += c;
					prev_state = state;
					state = 5;
					break;
				}
				if (c != '}' && prev_state == 5)
				{
					tmp += c;
					prev_state = state;
					state = 5;
					break;
				}
				if ((c == '}') && (prev_state == 5))
				{
					tmp += c;
					ListValue* object = new ListValue(key, "");
					parse(tmp, object);
					obj->addLast(object);
					prev_state = state;
					state = 6;
					break;
				}
			}
			case 6:
			{
				if ((c == '}') && (prev_state == 5))
				{
					break;
				}
				if ((c == ',') && (prev_state == 5))
				{
					prev_state = state;
					state = 1;
					break;
				}
			}
			}
		}
	}
}