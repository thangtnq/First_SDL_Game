#pragma once

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define THREAT_HEIGHT 33
#define THREAT_WIDTH 80
const int UNDER_LIMIT_THREAT = 200;

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& xBorder, const int& yBorder);
	void HandleInputAction(SDL_Event e);

	void set_xVal(const int& x) { xVal = x; }
	void set_yVal(const int& y) { yVal = y; }
	int get_xVal() const { return xVal; }
	int get_yVal() const { return yVal; }

	void set_AmoList(std::vector<AmoObject*> amoList)
	{
		p_AmoList = amoList;
	}
	std::vector<AmoObject*> get_AmoList() const { return p_AmoList; }

	void InitAmo(AmoObject* pAmo);
	void makeAmo(SDL_Surface* des, const int& xLimit, const int& yLimit);
	void Reset(const int& xborder);
	void ResetAmo(AmoObject* pAmo);
private:
	int xVal;
	int yVal;

	std::vector<AmoObject*> p_AmoList;
};

