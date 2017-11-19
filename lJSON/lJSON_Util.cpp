
#include "lJSON_Util.h"

#include "lJSON_Parser.h"
#include "lJSON_Printer.h"

void lJSON_Util::Parse(std::istream &in,liJSON_Value *&dest)
{
	lJSON_Parser Parser(in);
	Parser.Parse(dest);
}

void lJSON_Util::Print(const liJSON_Integer &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_Double &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_Bool &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_String &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_Object &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_Array &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	Printer.Visit(value);
}

void lJSON_Util::Print(const liJSON_Value &value,std::ostream &out)
{
	lJSON_Printer Printer(out);
	value.Accept(Printer);
}
