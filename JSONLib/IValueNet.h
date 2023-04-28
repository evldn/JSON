#pragma once
#include <string>
#include <iostream>
#include "IValue.h"
#include <msclr/marshal_cppstd.h>

namespace JSONLib {

	class IterIValue;
	class IValue;
	class Value;
	class ListValue;

	public ref class IValueNet abstract {
	public:
		virtual TypeValue getType() = 0;
		virtual System::String^ getKey() = 0;
		virtual System::String^ getValue() = 0;
	};

	public ref class ValueNet : public IValueNet {
		Value* val;
	public:
		ValueNet(System::String^ _key, System::String^ _val);
		TypeValue getType() override { return val->getType(); }
		System::String^ getKey() override;
		System::String^ getValue() override;
		Value* getVal() { return val; }
	};

	public ref class ListValueNet : public IValueNet {
		ListValue* listval;
	public:
		ListValueNet(System::String^ _key, System::String^ _value);
		~ListValueNet();
		TypeValue getType() override { return listval->getType(); }
		System::String^ getKey() override;
		System::String^ getValue() override;
		ListValue* getList() { return listval; }
		void addFirst(IValueNet^ _val);
		void addLast(IValueNet^ _val);
		void deleteFirst();
		void deleteLast();
	};
}