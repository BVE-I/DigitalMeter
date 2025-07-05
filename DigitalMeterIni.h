//
// Generated on 2025/07/06 by inimoni 
//

/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Documentation
  Struct = Section name, Field = Key name.
  The function used is only a declaration, load(), and save().
  The constructor automatically reads initialization file [initFileName].
  Please rewrite [initFileName] in the source freely.
  It becomes Windows folder when there is not path. The relative path can be used.

Example
#include "SampleIni.h"
void CTestDlg::OnButton1()
{
    //initFileName = "./sample.ini";
    SampleIni data1;                   // Open ./sample.ini
    int v = data1.Sample.value;        // [Sample]-value Get
    data1.Sample.value = v+1;          // [Sample]-value Modify
    data1.save();                      // Save ./Sample.ini (Opened file)

    SampleIni data2("sample.ini");     // Open C:/WINDOWS/Sample.ini
    data2.load("./sample.ini");        // Open Specified file.
    data2.save();                      // Save Opened file (Making at not being)
}

Supplementation
  Reading and writing becomes the unit of the file.
  [initFileName] is the same as the argument of GetPrivateProfileString() of SDK.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/

#ifndef DIGITALMETERINI_H
#define DIGITALMETERINI_H

#include <string>
using namespace std;

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#ifdef _UNICODE
	typedef std::wstring string_t;
#else
	typedef std::string string_t;
#endif

namespace inimoni{
    template<class T>
    static bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t);
};

/**
    DigitalMeter.ini input output class.
*/
class DigitalMeterIni
{
public:                                                                 
                                                                        
    DigitalMeterIni(string_t fname=_T(""))                          
    {                                                                   
        initFileName = _T("./DigitalMeter.ini"); //Default file.    
        init();                                                         
        load(fname);                                                    
    }                                                                   
                                                                        
    /**                                                                 
        INI file is read.                                               
        @param fname Filename                                           
        When there is not a file, It becomes initFileName.              
        When there is not a pass, It becomes Windows folder.            
    */                                                                  
    bool load(string_t fname=_T(""))                                  
    {                                                                   
        if(fname.empty()){                                              
            fname = initFileName;                                       
        }                                                               
        loadFileName = fname;                                           
        WIN32_FIND_DATA fd;                                             
        HANDLE h = ::FindFirstFile(fname.c_str(), &fd);                 
        if (h != INVALID_HANDLE_VALUE) {                                
            iniRW(fname,1);                                             
        }                                                               
        return (h != INVALID_HANDLE_VALUE);                             
    }                                                                   
                                                                        
    /**                                                                 
        It writes it in the INI file.                                   
        @param fname Filename                                           
        When there is not a file, It becomes open file.                 
        When there is not a pass, It becomes Windows folder.            
    */                                                                  
    bool save(string_t fname=_T(""))                                  
    {                                                                   
        if(fname.empty()){                                              
            fname = loadFileName;                                       
        }                                                               
        iniRW(fname,0);                                                 
        return true;                                                    
    }                                                                   

public:                                                                 

    // SpeedMeter
    struct _SpeedMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } SpeedMeter;

    // BCPressureMeter
    struct _BCPressureMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } BCPressureMeter;

    // MRPressureMeter
    struct _MRPressureMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } MRPressureMeter;

    // ERPressureMeter
    struct _ERPressureMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } ERPressureMeter;

    // BPPressureMeter
    struct _BPPressureMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } BPPressureMeter;

    // SAPPressureMeter
    struct _SAPPressureMeter
    {
        int      MeterIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } SAPPressureMeter;

    // CurrentMeter
    struct _CurrentMeter
    {
        string_t Type;
        int      MeterIndex;
        int      SignIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } CurrentMeter;

    // FirstPanelMeter
    struct _FirstPanelMeter
    {
        int      InputIndex;
        int      OutputIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } FirstPanelMeter;

    // SecondPanelMeter
    struct _SecondPanelMeter
    {
        int      InputIndex;
        int      OutputIndex;
        int      HundredsPlaceIndex;
        int      TenthPlaceIndex;
        int      OnesPlaceIndex;
        double   Increment;
        int      Interval;
    } SecondPanelMeter;

protected:

    string_t initFileName;
    string_t loadFileName;

    bool iniRW(string_t f, int r)    
    {                                
        string_t s;                  

        s = _T("SpeedMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), SpeedMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), SpeedMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), SpeedMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), SpeedMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), SpeedMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), SpeedMeter.Interval );

        s = _T("BCPressureMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), BCPressureMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), BCPressureMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), BCPressureMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), BCPressureMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), BCPressureMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), BCPressureMeter.Interval );

        s = _T("MRPressureMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), MRPressureMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), MRPressureMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), MRPressureMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), MRPressureMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), MRPressureMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), MRPressureMeter.Interval );

        s = _T("ERPressureMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), ERPressureMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), ERPressureMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), ERPressureMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), ERPressureMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), ERPressureMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), ERPressureMeter.Interval );

        s = _T("BPPressureMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), BPPressureMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), BPPressureMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), BPPressureMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), BPPressureMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), BPPressureMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), BPPressureMeter.Interval );

        s = _T("SAPPressureMeter");
        inimoni::inirw( r,f,s, _T("MeterIndex       "), SAPPressureMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), SAPPressureMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), SAPPressureMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), SAPPressureMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), SAPPressureMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), SAPPressureMeter.Interval );

        s = _T("CurrentMeter");
        inimoni::inirw( r,f,s, _T("Type             "), CurrentMeter.Type  );
        inimoni::inirw( r,f,s, _T("MeterIndex       "), CurrentMeter.MeterIndex );
        inimoni::inirw( r,f,s, _T("SignIndex        "), CurrentMeter.SignIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), CurrentMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), CurrentMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), CurrentMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), CurrentMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), CurrentMeter.Interval );

        s = _T("FirstPanelMeter");
        inimoni::inirw( r,f,s, _T("InputIndex       "), FirstPanelMeter.InputIndex );
        inimoni::inirw( r,f,s, _T("OutputIndex      "), FirstPanelMeter.OutputIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), FirstPanelMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), FirstPanelMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), FirstPanelMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), FirstPanelMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), FirstPanelMeter.Interval );

        s = _T("SecondPanelMeter");
        inimoni::inirw( r,f,s, _T("InputIndex       "), SecondPanelMeter.InputIndex );
        inimoni::inirw( r,f,s, _T("OutputIndex      "), SecondPanelMeter.OutputIndex );
        inimoni::inirw( r,f,s, _T("HundredsPlaceIndex"), SecondPanelMeter.HundredsPlaceIndex );
        inimoni::inirw( r,f,s, _T("TenthPlaceIndex  "), SecondPanelMeter.TenthPlaceIndex );
        inimoni::inirw( r,f,s, _T("OnesPlaceIndex   "), SecondPanelMeter.OnesPlaceIndex );
        inimoni::inirw( r,f,s, _T("Increment        "), SecondPanelMeter.Increment );
        inimoni::inirw( r,f,s, _T("Interval         "), SecondPanelMeter.Interval );
        return true;                                                    
    }                                                                   

    void init()                                                         
    {                                                                   
        SpeedMeter.MeterIndex        = 999;
        SpeedMeter.HundredsPlaceIndex = 999;
        SpeedMeter.TenthPlaceIndex   = 999;
        SpeedMeter.OnesPlaceIndex    = 999;
        SpeedMeter.Increment         = 1.0;
        SpeedMeter.Interval          = 200;
        BCPressureMeter.MeterIndex   = 999;
        BCPressureMeter.HundredsPlaceIndex = 999;
        BCPressureMeter.TenthPlaceIndex = 999;
        BCPressureMeter.OnesPlaceIndex = 999;
        BCPressureMeter.Increment    = 1.0;
        BCPressureMeter.Interval     = 200;
        MRPressureMeter.MeterIndex   = 999;
        MRPressureMeter.HundredsPlaceIndex = 999;
        MRPressureMeter.TenthPlaceIndex = 999;
        MRPressureMeter.OnesPlaceIndex = 999;
        MRPressureMeter.Increment    = 1.0;
        MRPressureMeter.Interval     = 200;
        ERPressureMeter.MeterIndex   = 999;
        ERPressureMeter.HundredsPlaceIndex = 999;
        ERPressureMeter.TenthPlaceIndex = 999;
        ERPressureMeter.OnesPlaceIndex = 999;
        ERPressureMeter.Increment    = 1.0;
        ERPressureMeter.Interval     = 200;
        BPPressureMeter.MeterIndex   = 999;
        BPPressureMeter.HundredsPlaceIndex = 999;
        BPPressureMeter.TenthPlaceIndex = 999;
        BPPressureMeter.OnesPlaceIndex = 999;
        BPPressureMeter.Increment    = 1.0;
        BPPressureMeter.Interval     = 200;
        SAPPressureMeter.MeterIndex  = 999;
        SAPPressureMeter.HundredsPlaceIndex = 999;
        SAPPressureMeter.TenthPlaceIndex = 999;
        SAPPressureMeter.OnesPlaceIndex = 999;
        SAPPressureMeter.Increment   = 1.0;
        SAPPressureMeter.Interval    = 200;
        CurrentMeter.Type            = _T("am");
        CurrentMeter.MeterIndex      = 999;
        CurrentMeter.SignIndex       = 999;
        CurrentMeter.HundredsPlaceIndex = 999;
        CurrentMeter.TenthPlaceIndex = 999;
        CurrentMeter.OnesPlaceIndex  = 999;
        CurrentMeter.Increment       = 1.0;
        CurrentMeter.Interval        = 200;
        FirstPanelMeter.InputIndex   = 999;
        FirstPanelMeter.OutputIndex  = 999;
        FirstPanelMeter.HundredsPlaceIndex = 999;
        FirstPanelMeter.TenthPlaceIndex = 999;
        FirstPanelMeter.OnesPlaceIndex = 999;
        FirstPanelMeter.Increment    = 1.0;
        FirstPanelMeter.Interval     = 200;
        SecondPanelMeter.InputIndex  = 999;
        SecondPanelMeter.OutputIndex = 999;
        SecondPanelMeter.HundredsPlaceIndex = 999;
        SecondPanelMeter.TenthPlaceIndex = 999;
        SecondPanelMeter.OnesPlaceIndex = 999;
        SecondPanelMeter.Increment   = 1.0;
        SecondPanelMeter.Interval    = 200;
    }                                                                   
};
typedef DigitalMeterIni DigitalMeterFile; //新旧互換

//---------------------------------------------------------------------------
// Common method                                                             
//---------------------------------------------------------------------------
#ifndef INIMONI_INIRW                                                        
#define INIMONI_INIRW                                                        
namespace inimoni                                                            
{                                                                            
    /*                                                                       
    Read and Write INI file                                                  
      int     is_read  1=Read mode, 0=Write mode                             
      string  fname    Filename (The Windows folder when there is not path)  
      string  sec      Section name                                          
      string  key      Key name                                              
      T       val_t    [Read]Init+Output, [Write]Input                       
    */                                                                       
    template<class T>                                                        
    bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t)
	{                                                                        
		if(is_read){                                                         
            inimoni::read(fname.c_str(), sec.c_str(), key.c_str(), val_t);   
        }                                                                    
        else{                                                                
			inimoni::write(fname.c_str(), sec.c_str(), key.c_str(), val_t);  
        }                                                                    
		return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, int& dst)            
    {                                                                        
        dst = GetPrivateProfileInt( sec.c_str(), key.c_str(), dst, ifn.c_str() );
        return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, basic_string<TCHAR>& dst)
    {                                                                        
        TCHAR buf[256];                                                      
        GetPrivateProfileString(                                             
            sec.c_str(),                                                     
            key.c_str(),                                                     
            dst.c_str(),                                                     
            buf,                                                             
            sizeof(buf),                                                     
            ifn.c_str() );                                                   
        dst = buf;                                                           
        return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, double& dst)         
    {                                                                        
        string_t s;                                                          
        inimoni::read(ifn, sec, key, s);                                     
                                                                             
        TCHAR* e;                                                            
        double x = _tcstod(s.c_str(), &e);                                   
                                                                             
        dst = 0.0;                                                           
        if (!*e) {                                                           
            dst = x;                                                         
        }                                                                    
        return true;                                                         
    }                                                                        
                                                                             
    template<class T>                                                        
    bool write(string_t ifn, string_t sec, string_t key, T val_t)            
    {                                                                        
        TCHAR val[1024];                                                     
        inimoni::to_string(val, val_t);                                      
        WritePrivateProfileString( sec.c_str(), key.c_str(), val, ifn.c_str() );
		return true;                                                    
	}                                                                   
                                                                        
    void to_string(TCHAR* str, int val)                                 
    {                                                                   
        _stprintf( str, _T("%d"), val );                                
    }                                                                   
                                                                        
    void to_string(TCHAR* str, double val)                              
    {                                                                   
        _stprintf( str, _T("%f"), val );                                
    }                                                                   
                                                                        
    void to_string(TCHAR* str, basic_string<TCHAR> val)                 
    {                                                                   
        _stprintf( str, _T("%s"), val.c_str() );                        
    }                                                                   
};                                                                      
                                                                        
#endif                                                                  
#endif                                                                  

