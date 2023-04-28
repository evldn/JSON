#include "IValue.h"

namespace JSONLib {
	IValue* IterListValue::Next() {
		if (!hasNext()) throw - 1;
		IValue* val = temp->val;
		temp = temp->next;
		return val;
	}
}
