// CLI_DelegateInterop.cpp : main project file.
//https://msdn.microsoft.com/en-US/library/367eeye0%28v=vs.80%29.aspx
// MarshalDelegate2.cpp
// compile with: /clr 

#include "stdafx.h"

#include <iostream>

using namespace System;
using namespace System::Runtime::InteropServices;

#pragma unmanaged

// Declare an unmanaged function type that takes two int arguments
// Note the use of __stdcall for compatibility with managed code
typedef int(__stdcall *ANSWERCB)(int, int);
static ANSWERCB cb;

int TakesCallback(ANSWERCB fp, int n, int m) {
  cb = fp;
  if (cb) {
    printf_s("[unmanaged] got callback address (%d), calling it...\n", cb);
    return cb(n, m);
  }
  printf_s("[unmanaged] unregistering callback");
  return 0;
}

#pragma managed

public delegate int GetTheAnswerDelegate(int, int);

int GetNumber(int n, int m) {
  Console::WriteLine("[managed] callback!");
  static int x = 0;
  ++x;

  return n + m + x;
}

static GCHandle gch;

int main() {
  GetTheAnswerDelegate^ fp = gcnew GetTheAnswerDelegate(GetNumber);

  gch = GCHandle::Alloc(fp);

  IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
  ANSWERCB cb = static_cast<ANSWERCB>(ip.ToPointer());
  Console::WriteLine("[managed] sending delegate as callback...");

  int answer = TakesCallback(cb, 243, 257);

  // possibly much later (in another function)...

  Console::WriteLine("[managed] releasing callback mechanisms...");
  TakesCallback(0, 243, 257);
  gch.Free();
}
