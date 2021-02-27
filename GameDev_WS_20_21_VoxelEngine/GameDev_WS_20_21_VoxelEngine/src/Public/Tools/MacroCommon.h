#pragma once

#define SIMPLEREADONLYATTRIB(type, name) \
private: \
	type _##name; \
	type##& get_##name() \
	{ \
		return _##name; \
	} \
public: \
	_declspec( property( get = get_##name ) ) type name; \

#define CUSTOMREADONLYATTRIB(type, name) \
private: \
	type _##name; \
	type##& get_##name(); \
public: \
	_declspec( property( get = get_##name ) ) type name; \

#define CUSTOMREADWRITEATTRIB(type, name) \
private: \
	type _##name; \
	type##& get_##name(); \
	void set_##name(type value); \
public: \
	_declspec( property( get = get_##name , put = set_##name ) ) type name; \
	