#include <Windows.h>			
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

vector<int> Get_PixelColor(int X, int Y) noexcept//Get screen pixel color
{
	static HDC Screen_HDC = GetWindowDC(NULL);
	const COLORREF Pixel = GetPixel(Screen_HDC, X, Y);
	return { GetRValue(Pixel), GetGValue(Pixel), GetBValue(Pixel) };
}
int main() noexcept//main thread
{
	system("cls");//clear console text
	system("title ");//console title

	while (true)//Loop
	{
		const vector<int> ScreenResolution = { GetSystemMetrics(SM_CXSCREEN) ,GetSystemMetrics(SM_CYSCREEN) };//Get system monitor pixels
		const auto New_PixelColor = Get_PixelColor(ScreenResolution[0] / 2 + 1, ScreenResolution[1] / 2 + 1);//Read the center position of the screen
		static auto Old_PixelColor = New_PixelColor;//initialization
		 
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)//trigger button
		{
			const auto ColorGap = 20;//To deal with shadow changes(in game)
			if (abs(New_PixelColor[0] - Old_PixelColor[0]) >= ColorGap || abs(New_PixelColor[1] - Old_PixelColor[1]) >= ColorGap || abs(New_PixelColor[2] - Old_PixelColor[2]) >= ColorGap)//check color
			{
				this_thread::sleep_for(chrono::milliseconds(200));// Delay to avoid fast trigger
				keybd_event(VK_INSERT, 0, 0, 0);
				this_thread::sleep_for(chrono::milliseconds(100));//Give the game program time to react
				keybd_event(VK_INSERT, 0, KEYEVENTF_KEYUP, 0);
				Old_PixelColor = New_PixelColor;//refresh
			}
		}
		else
		{
			Old_PixelColor = New_PixelColor;//Reset
		}
	}
	return 0;
}