// Ats.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "atsplugin.h"
#include "doorCloseingSecurity.h"
#include "DigitalMeterIni.h"
#include "SpeedMeter.h"
#include "PressureMeter.h"
#include "PanelMeter.h"
#include "DigitalMeter.h"
#include <stdio.h>
#include <cmath>

/// このATSプラグインの、コンピュータ上の絶対パス
char g_module_dir[MAX_PATH];
using namespace std;

BOOL APIENTRY DllMain(
	HINSTANCE hinstDLL,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:

	{
		char fullpath[MAX_PATH];
		char drive[MAX_PATH],
			dir[MAX_PATH];
		char* posIni;

		GetModuleFileNameA(hinstDLL, fullpath, MAX_PATH);
		_splitpath_s(fullpath, drive, MAX_PATH, dir, MAX_PATH, 0, 0, 0, 0);

		strcpy_s(g_module_dir, drive);
		strcat_s(g_module_dir, dir);

		//パスから.dllの位置を検索
		posIni = strstr(fullpath, ".dll");

		// .dllを.iniに置換
		memmove(posIni, ".ini", 4);

		// INIファイルをロードして結果を取得
		if (!g_ini.load(fullpath))
			g_ini.save(fullpath);
	}

	break;

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
}

ATS_API void WINAPI Initialize(int brake)
{
	g_speed = 0;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int* panel, int* sound)
{
	g_speed = vehicleState.Speed;
	g_output.Brake = g_brakeNotch;
	g_output.Power = g_powerNotch;
	g_output.Reverser = g_doorCloseingSecurity.main(g_pilotlamp, g_reverser); // 戸閉保安出力
	// 速度計
	g_SpeedMeter.main(vehicleState.Time, vehicleState.Speed, g_ini.SpeedMeter.Increment, g_ini.SpeedMeter.Interval);
	if (0 <= g_ini.SpeedMeter.MeterIndex && g_ini.SpeedMeter.MeterIndex <= 255)panel[g_ini.SpeedMeter.MeterIndex] = g_SpeedMeter.ToReturnMeter;
	if (0 <= g_ini.SpeedMeter.HundredsPlaceIndex && g_ini.SpeedMeter.HundredsPlaceIndex <= 255)panel[g_ini.SpeedMeter.HundredsPlaceIndex] = g_SpeedMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.SpeedMeter.TenthPlaceIndex && g_ini.SpeedMeter.TenthPlaceIndex <= 255)panel[g_ini.SpeedMeter.TenthPlaceIndex] = g_SpeedMeter.ToReturnTenthPlace;
	if (0 <= g_ini.SpeedMeter.OnesPlaceIndex && g_ini.SpeedMeter.OnesPlaceIndex <= 255)	panel[g_ini.SpeedMeter.OnesPlaceIndex] = g_SpeedMeter.ToReturnOnesPlace;
	// 圧力計関連
	g_BCPressureMeter.main(vehicleState.Time, vehicleState.BcPressure, g_ini.BCPressureMeter.Increment, g_ini.BCPressureMeter.Interval);
	if (0 <= g_ini.BCPressureMeter.MeterIndex && g_ini.BCPressureMeter.MeterIndex <= 255)panel[g_ini.BCPressureMeter.MeterIndex] = g_BCPressureMeter.ToReturnMeter;
	if (0 <= g_ini.BCPressureMeter.HundredsPlaceIndex && g_ini.BCPressureMeter.HundredsPlaceIndex <= 255)panel[g_ini.BCPressureMeter.HundredsPlaceIndex] = g_BCPressureMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.BCPressureMeter.TenthPlaceIndex && g_ini.BCPressureMeter.TenthPlaceIndex <= 255)panel[g_ini.BCPressureMeter.TenthPlaceIndex] = g_BCPressureMeter.ToReturnTenthPlace;
	if (0 <= g_ini.BCPressureMeter.OnesPlaceIndex && g_ini.BCPressureMeter.OnesPlaceIndex <= 255)panel[g_ini.BCPressureMeter.OnesPlaceIndex] = g_BCPressureMeter.ToReturnOnesPlace;
	g_MRPressureMeter.main(vehicleState.Time, vehicleState.MrPressure, g_ini.MRPressureMeter.Increment, g_ini.MRPressureMeter.Interval);
	if (0 <= g_ini.MRPressureMeter.MeterIndex && g_ini.MRPressureMeter.MeterIndex <= 255)panel[g_ini.MRPressureMeter.MeterIndex] = g_MRPressureMeter.ToReturnMeter;
	if (0 <= g_ini.MRPressureMeter.HundredsPlaceIndex && g_ini.MRPressureMeter.HundredsPlaceIndex <= 255)panel[g_ini.MRPressureMeter.HundredsPlaceIndex] = g_MRPressureMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.MRPressureMeter.TenthPlaceIndex && g_ini.MRPressureMeter.TenthPlaceIndex <= 255)panel[g_ini.MRPressureMeter.TenthPlaceIndex] = g_MRPressureMeter.ToReturnTenthPlace;
	if (0 <= g_ini.MRPressureMeter.OnesPlaceIndex && g_ini.MRPressureMeter.OnesPlaceIndex <= 255)panel[g_ini.MRPressureMeter.OnesPlaceIndex] = g_MRPressureMeter.ToReturnOnesPlace;
	g_ERPressureMeter.main(vehicleState.Time, vehicleState.ErPressure, g_ini.ERPressureMeter.Increment, g_ini.ERPressureMeter.Interval);
	if (0 <= g_ini.ERPressureMeter.MeterIndex && g_ini.ERPressureMeter.MeterIndex <= 255)panel[g_ini.ERPressureMeter.MeterIndex] = g_ERPressureMeter.ToReturnMeter;
	if (0 <= g_ini.ERPressureMeter.HundredsPlaceIndex && g_ini.ERPressureMeter.HundredsPlaceIndex <= 255)panel[g_ini.ERPressureMeter.HundredsPlaceIndex] = g_ERPressureMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.ERPressureMeter.TenthPlaceIndex && g_ini.ERPressureMeter.TenthPlaceIndex <= 255)panel[g_ini.ERPressureMeter.TenthPlaceIndex] = g_ERPressureMeter.ToReturnTenthPlace;
	if (0 <= g_ini.ERPressureMeter.OnesPlaceIndex && g_ini.ERPressureMeter.OnesPlaceIndex <= 255)panel[g_ini.ERPressureMeter.OnesPlaceIndex] = g_ERPressureMeter.ToReturnOnesPlace;
	g_BPPressureMeter.main(vehicleState.Time, vehicleState.BpPressure, g_ini.BPPressureMeter.Increment, g_ini.BPPressureMeter.Interval);
	if (0 <= g_ini.BPPressureMeter.MeterIndex && g_ini.BPPressureMeter.MeterIndex <= 255)panel[g_ini.BPPressureMeter.MeterIndex] = g_BPPressureMeter.ToReturnMeter;
	if (0 <= g_ini.BPPressureMeter.HundredsPlaceIndex && g_ini.BPPressureMeter.HundredsPlaceIndex <= 255)panel[g_ini.BPPressureMeter.HundredsPlaceIndex] = g_BPPressureMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.BPPressureMeter.TenthPlaceIndex && g_ini.BPPressureMeter.TenthPlaceIndex <= 255)panel[g_ini.BPPressureMeter.TenthPlaceIndex] = g_BPPressureMeter.ToReturnTenthPlace;
	if (0 <= g_ini.BPPressureMeter.OnesPlaceIndex && g_ini.BPPressureMeter.OnesPlaceIndex <= 255)panel[g_ini.BPPressureMeter.OnesPlaceIndex] = g_BPPressureMeter.ToReturnOnesPlace;
	g_SAPPressureMeter.main(vehicleState.Time, vehicleState.SapPressure, g_ini.SAPPressureMeter.Increment, g_ini.SAPPressureMeter.Interval);
	if (0 <= g_ini.SAPPressureMeter.MeterIndex && g_ini.SAPPressureMeter.MeterIndex <= 255)panel[g_ini.SAPPressureMeter.MeterIndex] = g_SAPPressureMeter.ToReturnMeter;
	if (0 <= g_ini.SAPPressureMeter.HundredsPlaceIndex && g_ini.SAPPressureMeter.HundredsPlaceIndex <= 255)panel[g_ini.SAPPressureMeter.HundredsPlaceIndex] = g_SAPPressureMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.SAPPressureMeter.TenthPlaceIndex && g_ini.SAPPressureMeter.TenthPlaceIndex <= 255)panel[g_ini.SAPPressureMeter.TenthPlaceIndex] = g_SAPPressureMeter.ToReturnTenthPlace;
	if (0 <= g_ini.SAPPressureMeter.OnesPlaceIndex && g_ini.SAPPressureMeter.OnesPlaceIndex <= 255)panel[g_ini.SAPPressureMeter.OnesPlaceIndex] = g_SAPPressureMeter.ToReturnOnesPlace;
	// パネル出力
	g_FirstPanelMeter.main(vehicleState.Time, panel[g_ini.FirstPanelMeter.InputIndex], g_ini.FirstPanelMeter.Increment, g_ini.FirstPanelMeter.Interval);
	if (0 <= g_ini.FirstPanelMeter.OutputIndex && g_ini.FirstPanelMeter.OutputIndex <= 255)	panel[g_ini.FirstPanelMeter.OutputIndex] = g_FirstPanelMeter.ToReturnMeter;
	if (0 <= g_ini.FirstPanelMeter.HundredsPlaceIndex && g_ini.FirstPanelMeter.HundredsPlaceIndex <= 255)panel[g_ini.FirstPanelMeter.HundredsPlaceIndex] = g_FirstPanelMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.FirstPanelMeter.TenthPlaceIndex && g_ini.FirstPanelMeter.TenthPlaceIndex <= 255)panel[g_ini.FirstPanelMeter.TenthPlaceIndex] = g_FirstPanelMeter.ToReturnTenthPlace;
	if (0 <= g_ini.FirstPanelMeter.OnesPlaceIndex && g_ini.FirstPanelMeter.OnesPlaceIndex <= 255)panel[g_ini.FirstPanelMeter.OnesPlaceIndex] = g_FirstPanelMeter.ToReturnOnesPlace;
	g_SecondPanelMeter.main(vehicleState.Time, panel[g_ini.SecondPanelMeter.InputIndex], g_ini.SecondPanelMeter.Increment, g_ini.SecondPanelMeter.Interval);
	if (0 <= g_ini.SecondPanelMeter.OutputIndex && g_ini.SecondPanelMeter.OutputIndex <= 255)panel[g_ini.SecondPanelMeter.OutputIndex] = g_SecondPanelMeter.ToReturnMeter;
	if (0 <= g_ini.SecondPanelMeter.HundredsPlaceIndex && g_ini.SecondPanelMeter.HundredsPlaceIndex <= 255)panel[g_ini.SecondPanelMeter.HundredsPlaceIndex] = g_SecondPanelMeter.ToReturnHundredsPlace;
	if (0 <= g_ini.SecondPanelMeter.TenthPlaceIndex && g_ini.SecondPanelMeter.TenthPlaceIndex <= 255)panel[g_ini.SecondPanelMeter.TenthPlaceIndex] = g_SecondPanelMeter.ToReturnTenthPlace;
	if (0 <= g_ini.SecondPanelMeter.OnesPlaceIndex && g_ini.SecondPanelMeter.OnesPlaceIndex <= 255)panel[g_ini.SecondPanelMeter.OnesPlaceIndex] = g_SecondPanelMeter.ToReturnOnesPlace;

	return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;
}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
}


ATS_API void WINAPI KeyUp(int hornType)
{
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex)
{
}

ATS_API void WINAPI DoorOpen()
{
	g_pilotlamp = false;
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;
}

ATS_API void WINAPI SetSignal(int signal)
{
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData)
{
}

ATS_API void WINAPI Load() 
{
}

ATS_API void WINAPI Dispose() 
{
}


