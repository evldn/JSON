#pragma once
#include <string>
#include <iostream>
#include "IValue.h"

namespace JSONLib 
{
	class JSon {
		ListValue* root;
	public:
		JSon() : root(new ListValue("root", "")) { }
		~JSon() { delete root; }
		void next();
		void down();
		void addFirst(IValue* val);
		void add(IValue* val);
		void deleteFirst();
		void del();
		ListValue* getRoot() { return root; }
		void back();
	};
}