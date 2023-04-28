#pragma once

#include <string>

namespace JSONLib
{
	class IterIValue;

	class IValue {
	public:
		virtual int getType() = 0;
		virtual std::string getKey() = 0;
		virtual std::string getValue() = 0;
		virtual IterIValue* iterator() = 0;
	};

	struct Link {
		Link* next;
		Link* prev;
		IValue* val;
	public:
		Link(IValue* _val) : next(nullptr), prev(nullptr), val(_val) {}
	};

	class IterIValue {
	public:
		virtual bool hasNext() = 0;
		virtual IValue* Next() = 0;
	};

	class IterValue : public IterIValue {
		IValue* val;
	public:
		IterValue(IValue* _val);
		bool hasNext() override;
		IValue* Next() override;
	};

	class IterListValue : public IterIValue {
		Link* temp;
		Link* tail;
	public:
		IterListValue(Link* head);
		bool hasNext() override;
		IValue* Next() override;
	};

	class Value :public IValue {
		std::string key;
		std::string val;
	public:
		Value(std::string _key, std::string _val);
		int getType();
		std::string getKey();
		std::string getValue();
		IterIValue* iterator();
	};

	class ListValue :public IValue {
		std::string key;
		std::string value;
	public:
		Link* head;
		Link* tail;
		ListValue(std::string _key, std::string _value);
		~ListValue();
		int getType();
		std::string getKey();
		IterIValue* iterator() { return new IterListValue(head); }
		std::string getValue();
	};
}