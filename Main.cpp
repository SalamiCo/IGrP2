//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("IGr.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("Ball.cpp");
USE("Ball.h", File);
USEUNIT("Pencil.cpp");
USE("Pencil.h", File);
USEUNIT("PV2D.cpp");
USEUNIT("Triangle.cpp");
USEUNIT("Circle.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
