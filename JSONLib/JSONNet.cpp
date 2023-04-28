#include "JSONNet.h"

namespace JSONLib 
{
	void JSONNet::next() {
		json->next();
		if (o != nullptr) {
			o->Refresh();
		}
	}
	void JSONNet::down() {
		json->down();
		if (o != nullptr) {
			o->Refresh();
		}
	}
	void JSONNet::addFirst(IValueNet^ _val) {
		if (_val->getType() == 1) {
			IValue* val = new Value(static_cast<ValueNet^>(_val)->getVal());
			json->addFirst(val);
		}
		if (_val->getType() == 2) {
			IValue* val = new ListValue(static_cast<ListValueNet^>(_val)->getList());
			json->addFirst(val);
		}
		if (o != nullptr) {
			o->Refresh();
		}
	}
	void JSONNet::add(IValueNet^ _val) {
		if (_val->getType() == 1) {
			IValue* val = new Value(static_cast<ValueNet^>(_val)->getVal());
			json->add(val);
		}
		if (_val->getType() == 2) {
			IValue* val = new ListValue(static_cast<ListValueNet^>(_val)->getList());
			json->add(val);
		}
		if (o != nullptr) {
			o->Refresh();
		}
	}
	void JSONNet::deleteFirst() {
		json->deleteFirst();
		if (o != nullptr) {
			o->Refresh();
		}
	}
	void JSONNet::del() {
		json->del();
		if (o != nullptr)
		{
			o->Refresh();
		}
	}
	void JSONNet::SetObserver(IObserver^ o)
	{
		this->o = o;
		o->Refresh();
	}
	void JSONNet::back()
	{
		json->back();
		if (o != nullptr) {
			o->Refresh();
		}
	}
}