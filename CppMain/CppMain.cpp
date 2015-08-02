// CppMain.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace CSharpModule;
using namespace System::Web;

namespace {
  void log (String^ msg) {
    Console::WriteLine (L"CppMain: {0}", msg);
  }

  void implNotifier0 () {
    log (L"implNotifier0 called");
  }

  void implNotifierHttpContext(HttpContext^ httpContext) {
    log (L"implNotifierHttpContext called");
    String^   expectedUrl = "/url";
    if (httpContext->Request->RawUrl != expectedUrl)
      log (L"wrong context");
    else
      log (L"OK context");
  }
}

int main (array<System::String ^> ^args) {
  try {
    CSharpClass^          worker = gcnew CSharpClass ();
    Notifier0^            notifier0 = gcnew Notifier0 (implNotifier0);
    NotifierHttpContext^  notifierHttpContext = gcnew NotifierHttpContext (implNotifierHttpContext);

    log (L"before notifier0");
    worker->process0(notifier0);
    log (L"after notifier0");

    log (L"before notifierHttpContext");
    worker->processHttpContext(notifierHttpContext);
    log (L"after notifierHttpContext");

  }
  catch (Exception^ ex) {
    Console::WriteLine (L"Exception: {0}", ex);
  }

  return 0;
}
