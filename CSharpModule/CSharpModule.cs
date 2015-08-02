using System;
using System.IO;
using System.Web;
using System.Web.Hosting;

namespace CSharpModule {
  public delegate void Notifier0();
  public delegate void NotifierHttpContext(HttpContext httpContext);

  public class CSharpClass {
    static void log(string msg) {
      Console.WriteLine ("CSharpClass: {0}", msg);
    }

    public void process0(Notifier0 notifier0) {
      log ("process0 before");
      notifier0 ();
      log ("process0 after");
    }

    public void processHttpContext(NotifierHttpContext notifierHttpContext) {
      try {
        TextWriter          tw = new StringWriter ();
        SimpleWorkerRequest wrq = new SimpleWorkerRequest ("/", ".", "url", "", tw);
        HttpContext         httpContext = new HttpContext (wrq);
        log ("processHttpContext before");
        notifierHttpContext (httpContext);
        log ("process0HttpContext after");
      }
      catch (Exception ex) {
        Console.WriteLine ("Exception: {0}", ex);
      }
    }
  }
}
