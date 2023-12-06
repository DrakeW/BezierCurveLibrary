#include "BezierCurve.h"

#include <iostream>


using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Renderer : public olc::PixelGameEngine
{
public:
	Renderer()
	{
		sAppName = "Renderer";
	}

private:

	Spline MainCurve = Spline(Curve(0, -150, 100, -150, 0, -100, 67, -98));

public:
	bool OnUserCreate() override
	{
		MainCurve.Add(150, -30, 130, -60);
		MainCurve.Add(200, -120, 150, -180);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		FillRect(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		int Samples = 500;

		for (int d = 0; d < MainCurve.Curves.size(); d++)
		{
			FillRect(MainCurve.Curves[d].R1x - 2, -MainCurve.Curves[d].R1y - 2, 4, 4, olc::MAGENTA);
			FillRect(MainCurve.Curves[d].R2x - 2, -MainCurve.Curves[d].R2y - 2, 4, 4, olc::MAGENTA);
			FillRect(MainCurve.Curves[d].P1x - 2, -MainCurve.Curves[d].P1y - 2, 4, 4, olc::GREEN);
			FillRect(MainCurve.Curves[d].P2x - 2, -MainCurve.Curves[d].P2y - 2, 4, 4, olc::RED);
		}

		for (float t = 0; t < Samples * MainCurve.Curves.size(); t++)
		{
			int Index = (int)(t / Samples);
			pair<float, float> Point = MainCurve.Curves[Index].GetPoint((t / Samples) - (float)Index);
			FillRect(Point.first, -Point.second, 1, 1, olc::RED);
		}

		MainCurve.MakeContinuous();

		MainCurve.Curves[0].R2y += 5 * fElapsedTime;
		
		return true;
	}

};

int main()
{
	Renderer demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}