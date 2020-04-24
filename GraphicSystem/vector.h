#pragma once
class vector
{
public:
	vector();
	~vector();
	virtual float& operator [] (const int i);
	float _value;
};

