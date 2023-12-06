#include "BezierCurve.h"

#include <iostream>


using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Renderer : public olc::PixelGameEngine
{
public:
	Renderer()
	{
		sAppName = "Renderer";
	}

private:
	vector<Curve> Curves;

public:
	bool OnUserCreate() override
	{
		Curves.push_back(Curve(0, -150, 100, -150, 0, -100, 67, -98));
		Continue(150, -30, 130, -60);
		Continue(200, -120, 150, -180);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		FillRect(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		int Samples = 500;

		for (int d = 0; d < Curves.size(); d++)
		{
			FillRect(Curves[d].R1x - 2, -Curves[d].R1y - 2, 4, 4, olc::MAGENTA);
			FillRect(Curves[d].R2x - 2, -Curves[d].R2y - 2, 4, 4, olc::MAGENTA);
			FillRect(Curves[d].P1x - 2, -Curves[d].P1y - 2, 4, 4, olc::GREEN);
			FillRect(Curves[d].P2x - 2, -Curves[d].P2y - 2, 4, 4, olc::RED);
		}

		for (float t = 0; t < Samples * Curves.size(); t++)
		{
			int Index = (int)(t / Samples);
			pair<float, float> Point = Curves[Index].FindPoint((t / Samples) - (float)Index);
			FillRect(Point.first, -Point.second, 1, 1, olc::RED);
		}

		MakeContinue();

		Curves[0].R2y += 5 * fElapsedTime;
		
		return true;
	}

	void Continue(int Rx, int Ry, int Px, int Py)
	{
		int LastIndex = Curves.size() - 1;
		Curves.push_back(Curve(Curves[LastIndex].R2x, Curves[LastIndex].R2y, Rx, Ry, Curves[LastIndex].R2x + (Curves[LastIndex].R2x - Curves[LastIndex].P2x), Curves[LastIndex].R2y + (Curves[LastIndex].R2y - Curves[LastIndex].P2y), Px, Py));
	}

	void MakeContinue()
	{
		for (int i = 1; i < Curves.size(); i++)
		{
			if (Curves[i].R1x != Curves[i - 1].R2x || Curves[i].R1y != Curves[i - 1].R2y)
			{
				Curves[i].R1x = Curves[i - 1].R2x;
				Curves[i].R1y = Curves[i - 1].R2y;
			}

			if (Curves[i].P1x != Curves[i - 1].R2x + (Curves[i - 1].R2x - Curves[i - 1].P2x) || Curves[i].P1y != Curves[i - 1].R2y + (Curves[i - 1].R2y - Curves[i - 1].P2y))
			{
				Curves[i].P1x = Curves[i - 1].R2x + (Curves[i - 1].R2x - Curves[i - 1].P2x);
				Curves[i].P1y = Curves[i - 1].R2y + (Curves[i - 1].R2y - Curves[i - 1].P2y);
			}
		}
	}
};

int main()
{
	Renderer demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}