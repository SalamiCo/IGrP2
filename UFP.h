//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
	__published:	// IDE-managed Components
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall FormResize(TObject *Sender);
		void __fastcall FormPaint(TObject *Sender);
		void __fastcall FormDestroy(TObject *Sender);

	private:	// User declarations
 		HDC hdc;
 		HGLRC hrc;
 		GLfloat xLeft,xRight,yTop,yBot;
 		GLfloat RatioViewPort;
 		//Center of the scene
		GLfloat centerX, centerY;
 		void __fastcall SetPixelFormatDescriptor();
 		void __fastcall GLScene();

 	public:		// User declarations
  		__fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
