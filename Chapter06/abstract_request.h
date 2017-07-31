/*
	abstractrequest.h - header file for the AbstractRequest class.
	
	Revision 0
	
	Notes:
			- 
			
	2016/11/19, Maya Posch
	(c) Nyanko.ws
*/


#pragma once
#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H


class AbstractRequest {
	//
	
public:
	virtual void setValue(int value) = 0;
	virtual void process() = 0;
	virtual void finish() = 0;
};

#endif
