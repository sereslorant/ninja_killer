#ifndef LJSON_UTIL_H
#define LJSON_UTIL_H

#include "liJSON.h"

#include "lJSON_TypeRetriever.h"

class lJSON_Util
{
public:
	
	static void Parse(std::istream &in,liJSON_Value *&dest);
	
	static void Print(const liJSON_Integer &value,std::ostream &out);
	static void Print(const liJSON_Double &value,std::ostream &out);
	static void Print(const liJSON_Bool &value,std::ostream &out);
	static void Print(const liJSON_String &value,std::ostream &out);
	static void Print(const liJSON_Object &value,std::ostream &out);
	static void Print(const liJSON_Array &value,std::ostream &out);
	
	static void Print(const liJSON_Value &value,std::ostream &out);
	
	static float FloatFromJSON(const liJSON_Value *json_value)
	{
		float value = 0.0;
		
		const liJSON_Integer *json_integer = ToConstInteger(json_value);
		const liJSON_Double *json_double = ToConstDouble(json_value);
		
		if(json_integer != nullptr)
			{value = json_integer->GetValue();}
		
		if(json_double != nullptr)
			{value = json_double->GetValue();}
		
		return value;
	}
	
	lJSON_Util(){}
	~lJSON_Util(){}
};

#endif // LJSON_UTIL_H
