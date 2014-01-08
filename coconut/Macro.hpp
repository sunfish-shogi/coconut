//
//  Macro.hpp
//  coconut
//
//  Created by Kubo Ryosuke on 2014/01/07.
//
//

#ifndef coconut_Macro_hpp
#define coconut_Macro_hpp

#define PROPERTY(type, name, funcName) \
private: type name; \
public: type get##funcName() { return name; } \
public: const type get##funcName() const { return name; } \
public: void set##funcName(type val) { name = val; }

#define PROPERTY_RO(type, name, funcName) \
private: type name; \
public: type get##funcName() { return name; } \
public: const type get##funcName() const { return name; }

#define PROPERTY_REF(type, name, funcName) \
private: type name; \
public: type& get##funcName() { return name; } \
public: const type& get##funcName() const { return name; } \
public: void set##funcName(const type& val) { name = val; }

#define PROPERTY_REF_RO(type, name, funcName) \
private: type name; \
public: type& get##funcName() { return name; } \
public: const type& get##funcName() const { return name; }

#define ARRAY_SIZE(a)				((int)(sizeof(a)/sizeof(a[0])))

#endif
