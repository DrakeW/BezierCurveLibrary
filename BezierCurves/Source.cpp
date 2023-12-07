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

	int SelectedIndex = 0;

	int SelectedPart = 0;

	float ControlSensitivity = 10;

	int Samples = 500;

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

		switch (SelectedPart)
		{
		case 0:
			FillRect(MainCurve.Curves[SelectedIndex].R1x - 3, -MainCurve.Curves[SelectedIndex].R1y - 3, 6, 6, olc::BLUE);
			break;
		case 1:
			FillRect(MainCurve.Curves[SelectedIndex].P1x - 3, -MainCurve.Curves[SelectedIndex].P1y - 3, 6, 6, olc::BLUE);
			break;
		case 2:
			FillRect(MainCurve.Curves[SelectedIndex].P2x - 3, -MainCurve.Curves[SelectedIndex].P2y - 3, 6, 6, olc::BLUE);
			break;
		case 3:
			FillRect(MainCurve.Curves[SelectedIndex].R2x - 3, -MainCurve.Curves[SelectedIndex].R2y - 3, 6, 6, olc::BLUE);
			break;
		default:
			break;
		}

		for (int d = 0; d < MainCurve.Curves.size(); d++)
		{
			FillRect(MainCurve.Curves[d].R1x - 2, -MainCurve.Curves[d].R1y - 2, 4, 4, olc::MAGENTA);
			FillRect(MainCurve.Curves[d].R2x - 2, -MainCurve.Curves[d].R2y - 2, 4, 4, olc::MAGENTA);
			FillRect(MainCurve.Curves[d].P1x - 2, -MainCurve.Curves[d].P1y - 2, 4, 4, olc::GREEN);

			if (d == MainCurve.Curves.size() - 1)
				FillRect(MainCurve.Curves[d].P2x - 2, -MainCurve.Curves[d].P2y - 2, 4, 4, olc::RED);
		}

		for (float t = 0; t < Samples * MainCurve.Curves.size(); t++)
		{
			int Index = (int)(t / Samples);
			pair<float, float> Point = MainCurve.Curves[Index].GetPoint((t / Samples) - (float)Index);
			FillRect(Point.first, -Point.second, 1, 1, olc::RED);
		}

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			ControlSensitivity *= 2;
		}
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			ControlSensitivity /= 2;
		}

		if (GetKey(olc::Key::SHIFT).bHeld)
		{

			if (GetKey(olc::Key::D).bPressed && SelectedIndex < MainCurve.Curves.size() - 1)
			{
				SelectedIndex += 1;
				SelectedPart = 0;
			}
			if (GetKey(olc::Key::A).bPressed && SelectedIndex > 0)
			{
				SelectedIndex -= 1;
				SelectedPart = 0;
			}
			if (GetKey(olc::Key::W).bPressed && SelectedPart < 3)
			{
				if (SelectedPart < 1 || SelectedIndex > MainCurve.Curves.size() - 2)
					SelectedPart += 1;
			}
			if (GetKey(olc::Key::S).bPressed && SelectedPart > 0)
			{
				SelectedPart -= 1;
			}

		}
		else
		{

			if (GetKey(olc::Key::W).bHeld)
			{
				switch (SelectedPart)
				{
				case 0:
					MainCurve.Curves[SelectedIndex].R1y += ControlSensitivity * fElapsedTime;
					break;
				case 1:
					MainCurve.Curves[SelectedIndex].P1y += ControlSensitivity * fElapsedTime;
					break;
				case 2:
					MainCurve.Curves[SelectedIndex].P2y += ControlSensitivity * fElapsedTime;
					break;
				case 3:
					MainCurve.Curves[SelectedIndex].R2y += ControlSensitivity * fElapsedTime;
					break;
				default:
					break;
				}
			}
			if (GetKey(olc::Key::S).bHeld)
			{
				switch (SelectedPart)
				{
				case 0:
					MainCurve.Curves[SelectedIndex].R1y -= ControlSensitivity * fElapsedTime;
					break;
				case 1:
					MainCurve.Curves[SelectedIndex].P1y -= ControlSensitivity * fElapsedTime;
					break;
				case 2:
					MainCurve.Curves[SelectedIndex].P2y -= ControlSensitivity * fElapsedTime;
					break;
				case 3:
					MainCurve.Curves[SelectedIndex].R2y -= ControlSensitivity * fElapsedTime;
					break;
				default:
					break;
				}
			}
			if (GetKey(olc::Key::D).bHeld)
			{
				switch (SelectedPart)
				{
				case 0:
					MainCurve.Curves[SelectedIndex].R1x += ControlSensitivity * fElapsedTime;
					break;
				case 1:
					MainCurve.Curves[SelectedIndex].P1x += ControlSensitivity * fElapsedTime;
					break;
				case 2:
					MainCurve.Curves[SelectedIndex].P2x += ControlSensitivity * fElapsedTime;
					break;
				case 3:
					MainCurve.Curves[SelectedIndex].R2x += ControlSensitivity * fElapsedTime;
					break;
				default:
					break;
				}
			}
			if (GetKey(olc::Key::A).bHeld)
			{
				switch (SelectedPart)
				{
				case 0:
					MainCurve.Curves[SelectedIndex].R1x -= ControlSensitivity * fElapsedTime;
					break;
				case 1:
					MainCurve.Curves[SelectedIndex].P1x -= ControlSensitivity * fElapsedTime;
					break;
				case 2:
					MainCurve.Curves[SelectedIndex].P2x -= ControlSensitivity * fElapsedTime;
					break;
				case 3:
					MainCurve.Curves[SelectedIndex].R2x -= ControlSensitivity * fElapsedTime;
					break;
				default:
					break;
				}
			}
		}

		MainCurve.MakeContinuous(true);

		//MainCurve.Curves[0].R2y += 5 * fElapsedTime;
		
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