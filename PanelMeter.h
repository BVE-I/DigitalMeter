#pragma once
class PanelMeter
{
private:
	bool Update;
	bool UpdateOld;
	float SaveData;
public:
	int ToReturnMeter;
	int ToReturnHundredsPlace;
	int ToReturnTenthPlace;
	int ToReturnOnesPlace;
	void main(int Time, int InputData, double Increment, int Interval) {
		Update = (bool)((Time / Interval) % 2);
		if (Update && !(UpdateOld))SaveData = abs(InputData);
		ToReturnMeter = (Increment > 1) ? (int(SaveData / Increment)) * Increment : (int(SaveData / Increment));
		ToReturnHundredsPlace = (SaveData < 100) ? 10 : (int)SaveData / 100;
		ToReturnTenthPlace = (SaveData < 10) ? 10 : (int)(SaveData / 10) % 10;
		ToReturnOnesPlace = (int)SaveData % 10;
		UpdateOld = Update;
	}
};

