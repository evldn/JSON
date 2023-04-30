#pragma once
#include <string>
#include <iostream>
#include "IValue.h"
#include <stack>

namespace JSONLib 
{

	class JSON {
		ListValue* root;
		IterIValue* jsonitr;
		IterIValue* jsonitrin;
		bool inobj = false;
		IValue* current;
		std::string str;
	public:
		JSON();
		~JSON() { delete root; }
		void load(std::string file_name);
		void parse(std::string input, ListValue* obj);
		void next();
		void down();
		void addFirst(IValue* val);
		void add(IValue* val);
		void deleteFirst();
		void del();
		void back();
		void up();
		IValue* getCurrent() { return current; }
		std::string getJSONString();
	};
}