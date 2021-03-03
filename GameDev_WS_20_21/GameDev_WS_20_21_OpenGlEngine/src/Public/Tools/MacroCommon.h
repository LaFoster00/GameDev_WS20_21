#pragma once

#define SIMPLE_READONLY_ATTRIB(type, name) \
private: \
	type _##name; \
public: \
	type## & get_##name() \
	{ \
		return _##name; \
	} \
	_declspec( property( get = get_##name ) ) type name; \

#define CUSTOM_READONLY_ATTRIB(type, name) \
private: \
	type _##name; \
public: \
	type##& get_##name(); \
	_declspec( property( get = get_##name ) ) type name; \

#define CUSTOM_READ_WRITE_ATTRIB(type, name) \
private: \
	type _##name; \
public: \
    type##& get_##name(); \
	void set_##name(type value); \
	_declspec( property( get = get_##name , put = set_##name ) ) type name; \
	