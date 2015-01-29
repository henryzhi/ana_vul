/*
//#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>


void main()
{

  HMODULE handle = LoadLibrary("kernel32.dll");
  if(handle)
  {
	FARPROC fp = GetProcAddress(handle, "NtUserLoadKeyboardLayoutEx");
	printf("function address: %lx\n", fp);
  
  
  }
  else 
	  printf("error\n");

  FreeLibrary(handle);
}
*/

//#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>

//typedef struct _UNICODE_STRING
//{
//	WORD Length;
//	WORD MaximumLength;
//	LPWSTR Buffer;
//} UNICODE_STRING, *PUNICODE_STRING;





void main()
{
        
 
    LoadKeyboardLayout("00008009",KLF_SETFORPROCESS);
	return;

}