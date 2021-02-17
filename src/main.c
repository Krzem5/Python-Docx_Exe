#define WINDOWS_LEAN_AND_MEAN
#include <payload.h>
#include <windows.h>
#include <shlwapi.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



#pragma warning(disable:4026)
int WinMain(void){
	char bf_tp[MAX_PATH];
	uint32_t r=GetTempPathA(MAX_PATH,bf_tp);
	if (!r||r>MAX_PATH){
		return 1;
	}
	char bf_fp[MAX_PATH];
	r=(uint32_t)(uintptr_t)PathCombineA(bf_fp,bf_tp,"what_is_an_exe.docx");
	if (!r){
		return 1;
	}
	HANDLE f=CreateFileA(bf_fp,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (f==INVALID_HANDLE_VALUE){
		return 1;
	}
	uint32_t l;
	WriteFile(f,PAYLOAD,PAYLOAD_SIZE,&l,NULL);
	CloseHandle(f);
	ShellExecuteA(NULL,"open",bf_fp,NULL,NULL,SW_SHOW);
	MessageBoxA(NULL,"How did this happen?","Word.exe?",MB_OK|MB_TOPMOST|MB_SYSTEMMODAL);
	return 0;
}
