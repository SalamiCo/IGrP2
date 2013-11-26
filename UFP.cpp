//Samuel Méndez Galán
//Pedro Morgado Alarcón

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
    tR = new Triangle(PV2D(xRight-30, yTop+20), PV2D(xRight-30, yBot-20), PV2D(xRight+300, yBot-20));
    tT = new Triangle(PV2D(xLeft-20, yTop-30), PV2D(xRight+20, yTop-30), PV2D(xRight+20, yTop+450));
    tL = new Triangle(PV2D(xLeft+30, yBot-20), PV2D(xLeft+30, yTop+20), PV2D(xLeft-300, yTop+20));
    tB = new Triangle(PV2D(xRight+20, yBot+30), PV2D(xLeft-20, yBot+30), PV2D(xLeft-20, yBot-450));

    t1 = new Triangle(PV2D(200, 0), PV2D(200, 200), PV2D(160, 160));
    t2 = new Triangle(PV2D(-250, 0), PV2D(-250, -150), PV2D(-210, -210));

    c1 = new Circle(PV2D(-200, 80), 30);
    c2 = new Circle(PV2D(250, -90), 30);

    obstacles.push_back(tR);
    obstacles.push_back(tT);
    obstacles.push_back(tL);
    obstacles.push_back(tB);
    obstacles.push_back(t1);
    obstacles.push_back(t2);
    obstacles.push_back(c1);
    obstacles.push_back(c2);

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

    Triangle::drawWalls(*tR,*tT,*tL,*tB);
    Triangle::drawTriangle(t1->getP1(), t1->getP2(), t1->getP3());
    Triangle::drawTriangle(t2->getP1(), t2->getP2(), t2->getP3());
    c1->drawCircle();
    c2->drawCircle();

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

    //Delete objects
    for(int i=0; i<obstacles.size(); ++i){
        delete obstacles[i];
    }
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
    Timer->Enabled = false;
    Step();
    Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void TGLForm2D::Step(){
    // Step
    //std::vector<Triangle>::iterator i;
    PV2D normalIn, normalHit, vectorMov = ball.getV();
    double tIn, tHitMin=vectorMov.vectorModule() + 0.2;
    bool exito = false;

    for(int i = 0; i <= 7; i++){
        if(obstacles[i]->intersection2Ball(ball.getCenter(), vectorMov.normalizeVector(), tIn, normalIn)){
            if(tIn>0 && tIn<=(1*vectorMov.vectorModule()+0.01)){
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
