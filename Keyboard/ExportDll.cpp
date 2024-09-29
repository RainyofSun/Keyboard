#include "stdafx.h"
#include "ExportDll.h"
#include "Shlwapi.h"
#include <atlstr.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool g_bopenData=false;
//CString g_strFileDirectory="";
bool StringToAsc(CString strKey)//判断是否为数字，字母等关键字是，返回false,不是返回true
{
	char* pszKey=strKey.GetBuffer(strKey.GetLength());
	for(int i=0;i<strKey.GetLength ();i++)
	{
		if(((pszKey[i]-30)>=0)&&((pszKey[i]-39)<=0))//是数字
		{
			strKey.ReleaseBuffer(); 
			return false;
		}
		if(((pszKey[i]-65)>=0)&&((pszKey[i]-90)<=0))//是字母
		{
			strKey.ReleaseBuffer(); 
			return false;			
		}
		if(((pszKey[i]-97)>=0)&&((pszKey[i]-122)<=0))//是字母
		{	
			strKey.ReleaseBuffer(); 
			return false;			
		}
	}
	strKey.ReleaseBuffer(); 
	return true;	
}
bool strLR(CString strLine, CString strKeyName)
{
	CString strL,strR;
	int a1;
	strLine.Remove (' ');
	a1=strLine.Find(strKeyName);   		
	//int n=strKeyName.GetLength ();//获取关键字长度
    //strL=strLine.Left(a1+n);//取得关键字
	strL=strLine.Left(a1);//要是strL为空证明关键字前面没有字母	
	strR=strLine;
	strR.Delete(0,(a1+strKeyName.GetLength()));
	strR.Delete(1,(strR.GetLength()-1));//要留一个字符判断左边必须为空
	if(StringToAsc(strR)&&(strL.IsEmpty ()))//不是字母数字
	{
		if(strR=="=")	
			return true;
	}
	return false;
}

void CreateInterfaceFont(CWnd *pWnd)
{
	CFont font;
	LOGFONT lf;
	lf.lfHeight=15; 
	lf.lfWidth =7;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=480;
	lf.lfItalic=false;
	lf.lfUnderline=false;
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfStrikeOut=false;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=DEFAULT_QUALITY;
	lf.lfPitchAndFamily=DEFAULT_PITCH;
	strcpy_s( lf.lfFaceName," ");
	font.CreateFontIndirect(&lf);
	pWnd->SendMessageToDescendants(WM_SETFONT,(WPARAM)HFONT(font),MAKELPARAM(TRUE,0)) ; 
}

bool OpenFileData(CString strFileName)
{
	CFileFind findFile;
	BOOL bTemp=findFile.FindFile(strFileName);
	if (TRUE==bTemp)
	{
		g_bopenData=true;
	//	g_strFileDirectory=strFileName;
		return true;
	}
	else
	{
		g_bopenData=false;
		return false;
	}
	return false;	
}

int ReadStringMem(CString strFind,CString *str,CString strFileDirectory)
{	
	if (strFileDirectory.IsEmpty())
	{
		*str="FINDKEYERROR";
		return -1;
	}
	char buffer[255];
	GetPrivateProfileString("DD",strFind,"FINDKEYERROR",buffer,255,strFileDirectory);
	*str=(CString)buffer;
	if (*str=="FINDKEYERROR")
	{
		return -1;
	}
	return 0;
}
int WriteStringMem(CString strKey, CString strWrite,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	BOOL bTemp=WritePrivateProfileString("DD",strKey,strWrite,strFileDirectory);
	if (FALSE==bTemp)
	{
	   return -1;
	}
    return 0;
}
int ReadNumDouble(CString strFile,double *Num,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		*Num=0;
		return -1;
	}
	char buffer[255];
	CString str;
	GetPrivateProfileString("DD",strFile,"FINDKEYERROR",buffer,255,strFileDirectory);
	str=(CString)buffer;
	if (str=="FINDKEYERROR")
	{
		*Num=0;
		return -1;
	}
	else
	{
		*Num=(double)atof(str);
		return 0;
	}
}
int  WriteNumDouble(CString strKey, double num,CString strFileDirectory)
{
	if(strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strWrite;
	strWrite.Format("%f",num);
	BOOL bTemp=WritePrivateProfileString("DD",strKey,strWrite,strFileDirectory);
	if (FALSE==bTemp)
	{
		return -1;
	}
	return 0;
}
int ReadNumFloat(CString strFile,float *Num,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		*Num=0;
		return -1;
	}
	char buffer[255];
	CString str;
	GetPrivateProfileString("DD",strFile,"FINDKEYERROR",buffer,255,strFileDirectory);
	str=(CString)buffer;
	if (str=="FINDKEYERROR")
	{
		*Num=0;
		return -1;
	}
	else
	{
		*Num=(float)atof(str);
		return 0;
	}
}
int WriteNumFloat(CString strKey, float num,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strWrite;
	strWrite.Format("%f",num);
	BOOL bTemp=WritePrivateProfileString("DD",strKey,strWrite,strFileDirectory);
	if (FALSE==bTemp)
	{
		return -1;
	}
	return 0;
}

int ReadNumLong(CString strFile,long *Num,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		*Num=0;
		return -1;
	}
	int nTempNum=0;
	nTempNum=GetPrivateProfileInt("DD",strFile,-80000,strFileDirectory);
	*Num=(long)nTempNum;		
	if (*Num==-80000)
	{
		*Num=0;
		return -1;
	}
	return 0;
}
int  WriteNumLong(CString strKey,long num,CString strFileDirectory)
{
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strTemp;
	strTemp.Format("%d",num);
	BOOL bTemp=WritePrivateProfileString("DD",strKey,strTemp,strFileDirectory);
	if (FALSE==bTemp)
	{
		return -1;
	}
	return 0;
}
int  ReadLongArray(CString strKey,long NumArray[],int nSize,CString strFileDirectory)//返回数组大小
{//这里的nSize必须是由外部传进来的，如果由内部确定很容易出错
	int i=0;
	for (i=0;i<nSize;i++)
	{
		NumArray[i]=0;
	}
	if (nSize<1)
	{
        for (i=0;i<nSize;i++)
        {
			NumArray[i]=0;
        }
		return -1;
	}
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strTemp;
	char buffer[255];
	CString strKeyTemp;
	for ( i=0;i<nSize;i++)
	{
		strKeyTemp=strKey;
		strTemp.Format("%d",i);
		strKeyTemp+=strTemp;
		GetPrivateProfileString("DD",strKeyTemp,"FINDKEYERROR",buffer,255,strFileDirectory);
		strTemp=(CString)buffer;
		if ("FINDKEYERROR"==strTemp)
		{
			NumArray[i]=0;
		}
		else
		{
			NumArray[i]=atol(buffer);
		}
	}
	return 0;
}
int  WriteLongArray(CString strKey,long NumArray[],int nSize,CString strFileDirectory)
{
	if (nSize<1)
	{
		return -1;
	}
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
		CString strTemp;
		CString strKeyTemp;
		BOOL bTemp=FALSE;
	    for (int i=0;i<nSize;i++)
		{
			strTemp.Format("%d",i);
			strKeyTemp=strKey;
			strKeyTemp+=strTemp;
			strTemp.Format("%d",NumArray[i]);
			bTemp=WritePrivateProfileString("DD",strKeyTemp,strTemp,strFileDirectory);
			if (FALSE==bTemp)
			{
				return -1;
			}
		}
	return 0;
}
int  ReadDoubleArray(CString strKey,double NumArray[],int nSize,CString strFileDirectory)//返回数组大小
{
	int i=0;
	for (i=0;i<nSize;i++)
	{
		NumArray[i]=0;
	}
	if (nSize<1)
	{	
		return -1;
	}
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strTemp;
	char buffer[255];
	
	CString strKeyTemp;
	for (i=0;i<nSize;i++)
	{
		strKeyTemp=strKey;
		strTemp.Format("%d",i);
		strKeyTemp+=strTemp;
		GetPrivateProfileString("DD",strKeyTemp,"FINDKEYERROR",buffer,255,strFileDirectory);
		strTemp=(CString)buffer;
		if ("FINDKEYERROR"==strTemp)
		{
			NumArray[i]=0;
		}
		else
		{
			NumArray[i]=(double)atof(buffer);
		}
	}		
	return 0;
}

int  WriteDoubleArray(CString strKey,double NumArray[],int nSize,CString strFileDirectory)//写入Double型数组
{
	if (nSize<1)
	{
		return -1;
	}
	if (strFileDirectory.IsEmpty())
	{
		return -1;
	}
	CString strTemp;
	CString strKeyTemp;
	BOOL bTemp=FALSE;
	for (int i=0;i<nSize;i++)
	{
		strKeyTemp=strKey;
		strTemp.Format("%d",i);
		strKeyTemp+=strTemp;
		strTemp.Format("%f",NumArray[i]);
		bTemp=WritePrivateProfileString("DD",strKeyTemp,strTemp,strFileDirectory);
		if (FALSE==bTemp)
		{
			return -1;
		}
	}
	return 0;
}
void SaveWriteData( )//将列表内容写入文件，清空列表
{
//	g_strFileDirectory.Empty ();
//	g_bopenData=false;
}
void   ReadFileFinish()
{
//	g_bopenData=false;
//	g_strFileDirectory.Empty ();
}
double VarsMmToInch(int Imm)
{
	return Imm*0.03937;
}
double  VarsInchToMm(int Inch )
{
    return Inch*24.400051;
}


unsigned int   DeleteTheFile(CString fileDir)
{
	if(!DeleteFile(fileDir))//如果删除文件夹报错
	{
		DWORD ret=::GetLastError ();
		return ret;
	}
	return 0;
}
unsigned int   CopyTheFile(CString fileSource,CString fileDes)
{
	if(!CopyFile(fileSource,fileDes,true))
	{
		DWORD ret=::GetLastError();
		return ret;
	}
	return 0;
}
unsigned int   MoveTheFile(CString fileSource,CString fileDes)
{
	if(!MoveFileEx(fileSource,fileDes,MOVEFILE_COPY_ALLOWED))
	{
		DWORD ret=::GetLastError();
		return ret;
	}
	return 0;
}
unsigned int   RenameTheFile(CString fileSource,CString fileRename)//如果不成功可能是文件不存在注意后缀
{//或者文件已经存在
	if(!MoveFile(fileSource,fileRename))
	{
		DWORD ret=::GetLastError();
		return ret;
	}
	return 0;
}
unsigned int   CreateTheDir(CString dirName)
{
	if(!CreateDirectory(dirName,NULL))
	{
		DWORD ret=::GetLastError();
		return ret;
	}
	return 0;
}
unsigned int   DeleteTheDir(CString dirName)
{
	CFileFind find;
    CString str;
	str=dirName;
	if(str.Right (1)!="\\")
		str+="\\";
	str+="*.*";
	BOOL bFind=find.FindFile (str);
	while(bFind)
	{
		bFind=find.FindNextFile();
		if(find.IsDirectory ()&&!find.IsDots ())
			DeleteTheDir(find.GetFilePath ());
		else
		{
			if(!find.IsDirectory ()&&!find.IsDots ())
				DeleteFile(find.GetFilePath ());
		}
	}
	find.Close ();
	if(!RemoveDirectory(dirName))
	{
		DWORD ret=::GetLastError();
		return ret;
	}
	return 0;
}


bool FileIsEmpty(CString strFile)
{
	CStdioFile file;
	CString strLine;
	if(file.Open (strFile,CFile::modeReadWrite|CFile::shareDenyNone)==NULL)
	{
		return false;
	}
	else
	{
		if(file.ReadString (strLine)!=NULL)
			return true;
		else
			return false;
	}
}

void LogWriteLog(CString strEventId, CString strEventData)
{
	CTime Currenttime;
	CString time;
	Currenttime=CTime::GetCurrentTime ();
	time=Currenttime.Format (_T("%Y/%m/%d/%H:%M:%S"));
    //获取当前时间
	int nMonth=0,nDay=0,nYear=0;//月日
	CString strDate,strMonth,strDay,strYear;//存放转换为字符串的月日
	nMonth=Currenttime.GetMonth ();//月份
	nDay=Currenttime.GetDay ();//日
	nYear=Currenttime.GetYear ();//年份文件夹名
	strYear.Format ("%d",nYear);
	strMonth.Format ("%d",nMonth);
	strDay.Format ("%d",nDay);
	if(nMonth<10)
	{
		strDate+="0";
	}
	strDate+=strMonth;
	if(nDay<10)
	{
		strDate+="0";
	}
    strDate+=strDay;
	//获取文件名
	strDate+=".log";//文件后缀
	CString strFileName;
	strFileName="..\\bin\\LOG\\";
	strFileName+=strYear;
	strFileName+="\\";
    //判断文件夹是否存在不存在则创建，存在则写入
    if(!PathFileExists(strFileName))//不存在
	{
		CreateDirectory(strFileName,NULL);
	}
	
	strFileName+=strDate;
	//文件保存路径
	CString stringTemp;
    stringTemp+=time;
	stringTemp+=",";
	stringTemp+=strEventId;
	stringTemp+=",";
	stringTemp+=strEventData;

	stringTemp+="\n";
	CStdioFile file;
	BOOL bTemp=file.Open (strFileName,CFile::modeReadWrite|CFile::modeNoTruncate|CFile::modeCreate|CFile::shareDenyNone);
		
	if (TRUE==bTemp)
	{
		file.SeekToEnd ();
		file.WriteString (stringTemp);
	    file.Close ();
	}
	//把要写入的内容按格式整合	
}
HBITMAP GetDLLBmpRes(CString strDllFile, UINT nResID)
{
	HINSTANCE hDLL = LoadLibrary( strDllFile );
	ASSERT (hDLL );
	if (hDLL != NULL)
	{
		AfxSetResourceHandle( hDLL );
	}
	HBITMAP h;
	h = LoadBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(nResID), RT_BITMAP), MAKEINTRESOURCE(nResID));
	ASSERT(h);
	if ( hDLL )
		FreeLibrary( hDLL );
	return h;
}
HICON GetDLLIconRes(CString strDllFile, UINT nResID)
{
	HINSTANCE hDLL = LoadLibrary( strDllFile );
	ASSERT (hDLL );
	if (hDLL != NULL)
	{
		AfxSetResourceHandle( hDLL );
	}
	HICON h;
	h = LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID));
	ASSERT(h);
	if ( hDLL )
		FreeLibrary( hDLL );
	
	return h;
}
CString  GetDLLStringRes(CString strDllFile,UINT nResID)
{
	HINSTANCE hDLL = LoadLibrary( strDllFile );
	
	ASSERT (hDLL );
	
	if (hDLL != NULL)
	{
		AfxSetResourceHandle( hDLL );
	}
	TCHAR ch[128];
	LoadString(hDLL,nResID,ch,128) ;
	if ( hDLL )
		FreeLibrary( hDLL );
	return ch;
}



//////////////add file read/write style///////////////////
BOOL MyWriteProfileString( const CString strSection, const CString strEntry,
	const CString strValue, const CString strIniPath )
{
	BOOL bValue = FALSE;
	bValue = ::WritePrivateProfileString(strSection, strEntry, strValue, strIniPath);
	return bValue;
}

BOOL MyGetProfileString( const CString strSection, const CString strEntry,
	CString & strValue, const CString strIniPath )
{
	::GetPrivateProfileString(strSection, strEntry,  _T(""), strValue.GetBuffer(MAX_PATH), MAX_PATH, strIniPath);
	if (strValue == _T(""))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL MyWriteProfileChar(const CString strSection, const CString strEntry, 
	const char chValue, const CString  strIniPath)
{
	CString strValue = _T("");
	strValue.Format(_T("%c"), chValue);
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}

BOOL MyGetProfileChar( const CString strSection, const CString strEntry,
	char & chMychar, const CString strIniPath )
{
	CString strMyString = _T("");
	CString strResult = _T("");
	char chResult = '\0';
	char *pTemp = NULL;
	strMyString.Format(_T("%c"), chMychar);
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		chMychar = '\0';
		return FALSE;
	}
	pTemp = (LPSTR)(LPCTSTR)(strResult);
	chResult = pTemp[0];
	chMychar = chResult; 
	return TRUE;
}

BOOL MyWriteProfileBool(const CString strSection, const CString strEntry, 
	const bool bValue, const CString  strIniPath)
{
	CString strValue = _T("");
	if (bValue)
	{
		strValue = _T("true");
	} 
	else
	{
		strValue = _T("false");
	}
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}

BOOL MyGetProfileBool( const CString strSection, const CString strEntry,
	bool & bValue, const CString strIniPath )
{
	CString strMyString = _T("");
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		bValue = false;
		return FALSE;
	}
	if (_T("true") == strMyString)
	{
		bValue = true;
	}
	else if (_T("false") == strMyString)
	{
		bValue = false;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL MyWriteProfileInt( const CString strSection, const CString strEntry, 
	const int nValue, const CString strIniPath )
{
	CString strValue = _T("");
	strValue.Format(_T("%d"), nValue);
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}

BOOL MyGetProfileInt( const CString strSection, const CString strEntry,
	int  & nValue, const CString strIniPath )
{
	CString strMyString = _T("");
	int nResult = 0;
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		nValue = 0;
		return FALSE;
	}
	nResult = _ttoi(strMyString);
	nValue = nResult;
	return TRUE; 
}

BOOL MyWriteProfileDouble( const CString strSection, const CString strEntry,
	const double dValue, const CString strIniPath )
{
	CString strValue = _T("");
	strValue.Format(_T("%f"),dValue);
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}

BOOL MyGetProfileDouble( const CString strSection, const CString strEntry,
	double & dValue, const CString strIniPath )
{
	CString strMyString = _T("");
	double dResult = 0.0;
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		dValue = 0.0;
		return FALSE;
	}
	dResult = _ttof(strMyString);
	dValue = dResult;
	return TRUE; 
}


BOOL MyGetProfileShort( const CString strSection, const CString strEntry,
	short  & nValue, const CString strIniPath )
{
	CString strMyString = _T("");
	short nResult = 0;
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		nValue = 0;
		return FALSE;
	}
	nResult = _ttoi(strMyString);
	nValue = nResult;
	return TRUE; 
}

BOOL MyWriteProfileShort(const CString strSection, const CString strEntry, 
	const short nValue, const CString strIniPath)
{
	CString strValue = _T("");
	strValue.Format(_T("%d"), nValue);
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}
BOOL MyWriteProfileFloat(const CString strSection, const CString strEntry, 
	const float dValue, const CString strIniPath)
{
	CString strValue = _T("");
	strValue.Format(_T("%f"),dValue);
	return MyWriteProfileString(strSection, strEntry, strValue, strIniPath);
}
BOOL MyGetProfileFloat( const CString strSection, const CString strEntry,
	float & dValue, const CString strIniPath )
{
	CString strMyString = _T("");
	float dResult = 0.0;
	if(!MyGetProfileString(strSection, strEntry, strMyString, strIniPath))
	{
		dValue = 0.0;
		return FALSE;
	}
	dResult = _ttof(strMyString);
	dValue = dResult;
	return TRUE; 
}
CString GetProjFilePath()
{
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	CString strPath = _T("");
	strPath = exeFullPath;
	int i = 0, nTemp = 0;
	for(i = 0; i <= strPath.GetLength(); i ++)
	{	
		if("\\" == strPath.Mid(i, 1))
			nTemp = i;
	}
	strPath = strPath.Left(nTemp);		
	for(i = 0; i <= strPath.GetLength(); i ++)
	{	
		if("\\" == strPath.Mid(i, 1))
			nTemp = i;
	}
	strPath = strPath.Left(nTemp + 1);
	return strPath;
}
void WriteCollectData(CString strDescribe, CString strData)
{
	CString strFilePath, strFileName, strTime,strFolder;//文件夹名称;
	CTime now = CTime::GetCurrentTime();
	strFolder.Format(_T("Data\\Collect\\%d-%d"), now.GetYear(), now.GetMonth());
	strFolder = GetProjFilePath() + strFolder;
	if(!PathFileExists(strFolder))//文件夹不存在则创建
	{
		CreateDirectory(strFolder,NULL);
	}

	ofstream CollectFile;
	strFileName.Format(_T("Data\\Collect\\%d-%d\\%d-%d-%d.txt"),now.GetYear(), now.GetMonth(), now.GetYear(), now.GetMonth(), now.GetDay());
	strFilePath = GetProjFilePath() + strFileName;
	strTime.Format(_T("%d:%d:%2d "), now.GetHour(), now.GetMinute(), now.GetSecond());
	CollectFile.open(strFilePath, ios::app);
	CollectFile << strTime << left << setw(30)<< strDescribe << strData  <<endl;
	CollectFile.close();
}