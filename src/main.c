#define WINDOWS_LEAN_AND_MEAN
#include <payload.h>
#include <windows.h>
#include <shlwapi.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4026)



int WinMain(void){
	char fp[MAX_PATH];
	char del_cmd[54+MAX_PATH]="cmd.exe /c ping 1.1.1.1 -n 1 -w 3000>nul&del /f /q \"";
	uint32_t r=GetModuleFileNameA(NULL,fp,MAX_PATH);
	if (!r||r>MAX_PATH){
		return 1;
	}
	for (uint32_t i=0;i<r;i++){
		del_cmd[i+52]=fp[i];
	}
	del_cmd[r+52]='\"';
	del_cmd[r+53]=0;
	while (fp[r]!='/'&&fp[r]!='\\'){
		r--;
	}
	fp[++r]='w';
	fp[++r]='h';
	fp[++r]='a';
	fp[++r]='t';
	fp[++r]='_';
	fp[++r]='i';
	fp[++r]='s';
	fp[++r]='_';
	fp[++r]='a';
	fp[++r]='n';
	fp[++r]='_';
	fp[++r]='e';
	fp[++r]='x';
	fp[++r]='e';
	fp[++r]='.';
	fp[++r]='d';
	fp[++r]='o';
	fp[++r]='c';
	fp[++r]='x';
	fp[++r]=0;
	HANDLE f=CreateFileA(fp,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (f==INVALID_HANDLE_VALUE){
		return 1;
	}
	uint32_t l;
	WriteFile(f,PAYLOAD,PAYLOAD_SIZE,&l,NULL);
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
