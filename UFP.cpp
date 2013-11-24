//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormCreate(TObject *Sender)
{
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    	ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
    	ShowMessage("Could not MakeCurrent");
    //Cor de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    xRight=400.0; xLeft=-xRight;
    yTop=250; yBot=-yTop;
    //Radio del volumen de vista == 1

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;

    // inicialización de las variables del programa
    tR = Triangle(PV2D(xRight-30, yTop+20), PV2D(xRight-30, yBot-20), PV2D(xRight+300, yBot-20));
    tT = Triangle(PV2D(xLeft-20, yTop-30), PV2D(xRight+20, yTop-30), PV2D(xRight+20, yTop+450));
    tL = Triangle(PV2D(xLeft+30, yBot-20), PV2D(xLeft+30, yTop+20), PV2D(xLeft-300, yTop+20));
    tB = Triangle(PV2D(xRight+20, yBot+30), PV2D(xLeft-20, yBot+30), PV2D(xLeft-20, yBot-450));

    obstacleList.push_back(tR);
    obstacleList.push_back(tT);
    obstacleList.push_back(tL);
    obstacleList.push_back(tB);

    obstacleList.push_back(Triangle(PV2D(100, 0), PV2D(100, 100), PV2D(60, 60)));
    obstacleList.push_back(Triangle(PV2D(-100, 0), PV2D(-100, -100), PV2D(-60, -60)));

    //Set timer properties
    Timer->Enabled = false;
    Timer->Interval = 1;
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };
    int PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------
void __fastcall TGLForm2D::FormResize(TObject *Sender)
{

    if ((ClientWidth<=1)||(ClientHeight<=1)){
        ClientWidth=800;
        ClientHeight=500;
    }

    glViewport(0,0,ClientWidth,ClientHeight);

    centerX = (xLeft + xRight) / 2.0;
    xLeft = centerX - (ClientWidth / 2.0);
    xRight = centerX + (ClientWidth / 2.0);

    centerY = (yBot + yTop) / 2.0;
    yBot = centerY - (ClientHeight / 2.0);
    yTop = centerY + (ClientHeight / 2.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLScene();

}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Triangle::drawWalls(tR,tT,tL,tB);
    Triangle::drawTriangle(PV2D(100, 0), PV2D(100, 100), PV2D(60, 60));
    Triangle::drawTriangle(PV2D(-100, 0), PV2D(-100, -100), PV2D(-60, -60));
    ball.drawBall();

    glFlush();
    SwapBuffers(hdc);
}

//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
    GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
}
//---------------------------------------------------------------------------


void __fastcall TGLForm2D::FormKeyPress(TObject *Sender, char &Key)
{
    switch(Key){
        //Manual step
        case 's':
            Step();
            break;
        //Timer step
        case 't':
            if(Timer->Enabled){
                Timer->Enabled = false;
            } else {
                Timer->Enabled = true;
            }
            break;
        //Change timer interval
        case '1':
            Timer->Interval = 100;
            break;
        case '2':
            Timer->Interval = 50;
            break;
        case '3':
            Timer->Interval = 1;
            break;
    };

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLScene();
}
//---------------------------------------------------------------------------



void __fastcall TGLForm2D::TimerTimer(TObject *Sender)
{
    Step();
}
//---------------------------------------------------------------------------

void TGLForm2D::Step(){
    // Step
    std::vector<Triangle>::iterator i;
    PV2D normalIn, normalHit, vectorMov = ball.getV();
    double tIn, tHitMin=vectorMov.vectorModule() + 0.5;
    bool exito = false;

    for(i=obstacleList.begin(); i!=obstacleList.end(); ++i){
        if(i->intersection2Ball(ball.getCenter(), vectorMov.normalizeVector(), tIn, normalIn)){
            if(tIn>0.005 && tIn<=(1*vectorMov.vectorModule())){
                //ShowMessage("A DADO!");
                if(tIn < tHitMin){
                    tHitMin = tIn;
                    normalHit = normalIn;
                    exito = true;
                }
            }
        }
    }

    if(exito){
        ball.step(tHitMin);
        ball.rebound(normalHit);  
    } else {
        ball.step(1.0);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLScene();
}