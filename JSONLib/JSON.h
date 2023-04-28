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
	public:
		JSON() : root(new ListValue("root", "")), jsonitr(root->iterator()), current(jsonitr->Next()) { }
		~JSON() { delete root; }
		void next();
		void down();
		void addFirst(IValue* val);
		void add(IValue* val);
		void deleteFirst();
		void del();
		void back();
		IValue* getCurrent() { return current; }
		std::string getJSONString();
	};
}