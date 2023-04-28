#include "IValueNet.h"

namespace JSONLib {
	ValueNet::ValueNet(System::String^ _key, System::String^ _val) {
		std::string key = msclr::interop::marshal_as<std::string>(_key);
		std::string value = msclr::interop::marshal_as<std::string>(_val);
		val = new Value(key, value);
	}
	System::String^ ValueNet::getKey()
	{
		return gcnew System::String((val->getKey()).c_str());
	}
	System::String^ ValueNet::getValue()
	{
		return gcnew System::String((val->getValue()).c_str());
	}


	ListValueNet::ListValueNet(System::String^ _key, System::String^ _value)
	{
		std::string key = msclr::interop::marshal_as<std::string>(_key);
		std::string value = msclr::interop::marshal_as<std::string>(_value);
		listval = new ListValue(key, value);
	}
	ListValueNet::~ListValueNet()
	{
		delete listval;
	}
	System::String^ ListValueNet::getKey()
	{
		return gcnew System::String((listval->getKey()).c_str());
	}
	System::String^ ListValueNet::getValue()
	{
		return gcnew System::String((listval->getValue()).c_str());
	}
	void ListValueNet::addFirst(IValueNet^ _val)
	{
		if (_val->getType() == 1) {
			IValue* val = new Value(static_cast<ValueNet^>(_val)->getVal());
			listval->addFirst(val);
		}
		if (_val->getType() == 2) {
			IValue* val = new ListValue(static_cast<ListValueNet^>(_val)->getList());
			listval->addFirst(val);
		}
	}
	void ListValueNet::addLast(IValueNet^ _val)
	{
		if (_val->getType() == 1) {
			IValue* val = new Value(static_cast<ValueNet^>(_val)->getVal());
			listval->addLast(val);
		}
		if (_val->getType() == 2) {
			IValue* val = new ListValue(static_cast<ListValueNet^>(_val)->getList());
			listval->addLast(val);
		}
	}
	void ListValueNet::deleteFirst()
	{
		listval->deleteFirst();
	}
	void ListValueNet::deleteLast()
	{
		listval->deleteLast();
	}
}

