#ifndef _OBJECT_FACTORY_H
#define _OBJECT_FACTORY_H


template<class T>

class ObjectFactory{
public:
	ObjectFactory(){}
	~ObjectFactory(){}
public:
	T*	createObject(){
		return new T();
	}

};

#endif
