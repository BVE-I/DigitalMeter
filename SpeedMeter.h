#pragma once
#include <random>
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
		std::random_device seed;
		std::mt19937 engine(seed());
		double mu, sig;
		if (Increment < 1)mu = 0.0, sig = 0.12;
		else mu = 0.0, sig = 0.2;
		std::normal_distribution<> dist(mu, sig);
		double rand = dist(engine);
		double k = -exp(-fabs(Speed) / 25) + 1;
		if (Update && !(UpdateOld))SaveSpeed = fabsf(Speed + k * rand);
		ToReturnMeter = (Increment > 1) ? (int(SaveSpeed / Increment)) * Increment : (int(SaveSpeed / Increment));
		ToReturnHundredsPlace = (SaveSpeed < 100) ? 10 :(int)SaveSpeed / 100;
		ToReturnTenthPlace = (SaveSpeed < 10) ? 10 : (int)(SaveSpeed / 10) % 10;
		ToReturnOnesPlace = (int)SaveSpeed % 10;
		UpdateOld = Update;
	}
};

