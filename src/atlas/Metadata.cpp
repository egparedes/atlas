// (C) Copyright 1996-2014 ECMWF.

#include "atlas/Metadata.hpp"
#include "atlas/Field.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

#define METADATA( VALUE_TYPE ) \
template<>\
Metadata& Metadata::set(const std::string& name, const VALUE_TYPE& value)\
{\
  map_##VALUE_TYPE##_[name] = value;\
  return *this;\
}\
template<>\
VALUE_TYPE& Metadata::get(const std::string& name)\
{\
  try {\
    return map_##VALUE_TYPE##_.at(name);\
  }\
  catch( std::out_of_range& e ) {\
    std::stringstream msg;\
    msg << "Could not find metadata \"" << name << "\"";\
    throw std::out_of_range(msg.str());\
  }\
}

#define METADATA_C_BINDING( VALUE_TYPE ) \
void atlas__Metadata__add_##VALUE_TYPE (Metadata* This, const char* name, VALUE_TYPE value)\
{\
  This->set( std::string(name) ,value);\
}\
VALUE_TYPE atlas__Metadata__get_##VALUE_TYPE (Metadata* This, const char* name)\
{\
  return This->get<VALUE_TYPE>( std::string(name) );\
}


namespace atlas {

METADATA(bool)
METADATA(int)
METADATA(float)
METADATA(double)
METADATA(string)

// ------------------------------------------------------------------
// C wrapper interfaces to C++ routines

Metadata* atlas__Metadata__new () { 
  return new Metadata(); 
}

void atlas__Metadata__delete (Metadata* This) {
  delete This;
}

METADATA_C_BINDING(int)
METADATA_C_BINDING(float)
METADATA_C_BINDING(double)

void atlas__Metadata__add_string (Metadata* This, const char* name, const char* value)
{
  This->set( std::string(name), std::string(value) );
}
const char* atlas__Metadata__get_string (Metadata* This, const char* name)
{
  return This->get<std::string>( std::string(name) ).c_str();
}
// ------------------------------------------------------------------


} // namespace atlas

#undef METADATA
#undef METADATA_C_BINDING


