#pragma once
class Object
{
private:

public:
	double x;
	double y;
	Object();
	virtual ~Object();

	virtual bool run();
	virtual void draw();
};