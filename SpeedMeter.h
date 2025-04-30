#pragma once
class SpeedMeter
{
private:
	bool Update;
	bool UpdateOld;
	float SaveSpeed;
public:
	int ToReturnMeter;
	int ToReturnHundredsPlace;
	int ToReturnTenthPlace;
	int ToReturnOnesPlace;
	void main(int Time, float Speed, double Increment, int Interval) {
		Update = (bool)((Time / Interval) % 2);
		if (Update && !(UpdateOld))SaveSpeed = fabsf(Speed);
		ToReturnMeter = (Increment > 1) ? (int(SaveSpeed / Increment)) * Increment : (int(SaveSpeed / Increment));
		ToReturnHundredsPlace = (SaveSpeed < 100) ? 10 :(int)SaveSpeed / 100;
		ToReturnTenthPlace = (SaveSpeed < 10) ? 10 : (int)(SaveSpeed / 10) % 10;
		ToReturnOnesPlace = (int)SaveSpeed % 10;
		UpdateOld = Update;
	}
};

