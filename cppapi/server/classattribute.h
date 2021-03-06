//=============================================================================
//
// file :		ClassAttribute.h
//
// description :	Include file for the Tango attribute.
//			Three classes are declared in this file :
//
//			AttrProperty : A helper class. This class stored a couple
//				       property name, property value as strings
//		 	ClassAttribute : A class for each attribute with all
//					 its properties defined at the class
//					 level. The properties are still stored
//					 as string
//			MultiClassAttribute : A class to manage all the class
//					      level definition of attributes.
//					      There is one instance of this class
//					      for each tango device pattern
//
// project :		TANGO
//
// author(s) :		E.Taurel
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015
//						European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
// This file is part of Tango.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
//
// $Revision$
//
//=============================================================================

#ifndef _CLASS_ATTRIBUTE_H
#define _CLASS_ATTRIBUTE_H

#include <tango.h>
//#include <attrdesc.h>
#include <functional>

namespace Tango
{

//=============================================================================
//
//			The AttrProperty class
//
//
// description :	This class is used to store a pair of attribute name,
//			attribute value. Both name and value are stored as
//			string
//
//=============================================================================

class AttrProperty
{
public:
	AttrProperty(const char *name,const char *value);
	AttrProperty(string &name,string &value);
	AttrProperty(const char *name,long value);
	AttrProperty(const char *name,string &value);
	~AttrProperty() {};

	string &get_value() {return attr_value;}
	long get_lg_value() {return attr_lg;}
	string &get_name() {return attr_name;}

	void convert(const char *);

#ifndef TANGO_HAS_LOG4TANGO
	friend ostream &operator<<(ostream &,const AttrProperty &);
#endif

private:
	string			attr_name;
	string			attr_value;
	long			attr_lg;
};


//=============================================================================
//
//			The MultiClassAttribute class
//
//
// description :	This class is a holder for all the ClassAttribute
//			instance. There is one instance of this class for each
//			Tango device pattern implementation. This instance is
//			stored in the DeviceClass object of the pattern
//
//=============================================================================


class MultiClassAttribute
{
public:
	MultiClassAttribute();
	~MultiClassAttribute();

	void init_class_attribute(string &class_name,long base = 0);

	vector<Tango::Attr *> &get_attr_list() {return attr_list;}
	Attr &get_attr(string &attr_name);
	void remove_attr(const string &,const string &);

protected:
	vector<Tango::Attr *>			attr_list;
};


//=============================================================================
//
//			A binary function object
//
//
// description :	This binary function object is used by the find_if
//			std C++ find_if algorithm. It checks if the
//			ClassAttribute object passed as argument (A1) stored
//			all the properties for the atribute name passed as
//			second argument (A2).
//			This function object is a predicate and therefore
//			returns a boolean (R)
//
//=============================================================================

template <class A1, class A2, class R>
struct WantedClassAttr : public  binary_function<A1,A2,R>
{
	R operator() (A1 att,A2 name_str) const
	{
		return att->get_name() == name_str;
	}
};

} // End of Tango namespace

#endif // _CLASS_ATTRIBUTE_H
