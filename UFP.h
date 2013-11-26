//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <gl\gl.h>
#include <gl\glu.h>

#include "Ball.h"
#include "Triangle.h"
#include "Circle.h"

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
	__published:	// IDE-managed Components
        TTimer *Timer;
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall FormResize(TObject *Sender);
		void __fastcall FormPaint(TObject *Sender);
		void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall TimerTimer(TObject *Sender);

	private:	// User declarations
 		HDC hdc;
 		HGLRC hrc;
 		GLfloat xLeft,xRight,yTop,yBot;
 		GLfloat RatioViewPort;
 		//Center of the scene
		GLfloat centerX, centerY;
		// Ball
		Ball ball;
		//Walls
		Triangle *tR, *tT, *tL, *tB, *t1, *t2;
		// Obstacle's list
		std::vector<Obstacle*> obstacles;
		//Circles
		Circle *c1, *c2;

 		void __fastcall SetPixelFormatDescriptor();
 		void __fastcall GLScene();
 		void Step();

 	public:		// User declarations
  		__fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
