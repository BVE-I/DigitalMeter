#pragma once
class PressureMeter
{
private:
	bool Update;
	bool UpdateOld;
	float SavePressure;
public:
	int ToReturnMeter;
	int ToReturnHundredsPlace;
	int ToReturnTenthPlace;
	int ToReturnOnesPlace;
	void main(int Time, float Pressure, double Increment, int Interval) {
		Update = (bool)((Time / Interval) % 2);
		if (Update != UpdateOld)SavePressure = Pressure;
		ToReturnMeter = (Increment > 1) ? (int(SavePressure / Increment)) * Increment : (int(SavePressure / Increment));
		ToReturnHundredsPlace = (SavePressure < 100) ? 10 : (int)SavePressure / 100;
		ToReturnTenthPlace = (SavePressure < 10) ? 10 : (int)(SavePressure / 10) % 10;
		ToReturnOnesPlace = (int)SavePressure % 10;
		UpdateOld = Update;
	}
};

