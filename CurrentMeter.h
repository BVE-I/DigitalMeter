#pragma once
class CurrentMeter
{
private:
	bool Update;
	bool UpdateOld;
	float SaveCurrent;
public:
	int ToReturnSign;
	int ToReturnMeter;
	int ToReturnHundredsPlace;
	int ToReturnTenthPlace;
	int ToReturnOnesPlace;
	void main(int Time, float Current, double Increment, int Interval, string Type) {
		Update = (bool)((Time / Interval) % 2);
		if (Update && !(UpdateOld))SaveCurrent = (Type == "amabs") ? fabs(Current) : Current;
		ToReturnSign = (SaveCurrent == 0) ? 0 : (SaveCurrent < 0) ? 2 : 1;
		ToReturnMeter = (Increment > 1) ? (int(SaveCurrent / Increment)) * Increment : (int(SaveCurrent / Increment));
		ToReturnHundredsPlace = (SaveCurrent < 100) ? 10 : (int)SaveCurrent / 100;
		ToReturnTenthPlace = (SaveCurrent < 10) ? 10 : (int)(SaveCurrent / 10) % 10;
		ToReturnOnesPlace = (int)SaveCurrent % 10;
		UpdateOld = Update;
	}
};

