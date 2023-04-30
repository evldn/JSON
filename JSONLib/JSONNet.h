#pragma once
#include "JSON.h"
#include "IValueNet.h"
#include <msclr/marshal_cppstd.h>

namespace JSONLib {
	public ref class IObserver abstract {
	public:
		virtual void Refresh() abstract;
	};

	public ref class JSONNet {
		JSON* json;
		IObserver^ o;
	public:
		JSONNet() : json(new JSON()) { }
		~JSONNet() { delete json; }
		void load(System::String^ file_name);
		void next();
		void down();
		void addFirst(IValueNet^ _val);
		void add(IValueNet^ _val);
		void deleteFirst();
		void del();
		void SetObserver(IObserver^ o);
		void back();
		void up();
		System::String^ getJsonString() {return gcnew System::String(json->getJSONString().c_str()); }
	};
}