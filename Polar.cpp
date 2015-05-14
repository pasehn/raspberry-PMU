//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Polar.h"
#include "Unit1.h"
#include "global.h"
#include "conflinear.h"
#include "Linear.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeePolar"
#pragma link "TeeProcs"
#pragma link "TeeEdit"
#pragma link "TeeAntiAlias"
#pragma link "TeeChartGrid"
#pragma link "TeeTools"
#pragma link "TeeSubChart"
#pragma resource "*.dfm"

TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormCreate(TObject *Sender)
{
//TPolarSeries **serie_pol;  //vetor de series polar

serie_pol = (TPolarSeries **)malloc(2*dados.num_terminais*sizeof(TPolarSeries *)); //redimensiona

for (int i = 0; i < dados.num_terminais; i++) { //para todas as pmus
	serie_pol[i] = new TPolarSeries(Chart6); //nova serie
	serie_pol[i]->Title = (dados.pmu[i].Nome + "(T)").c_str();  //titulo da serie
	serie_pol[i]->ParentChart = Chart6; //parent chart
	serie_pol[i]->AddPolar(0,0,"",clWhite);  //adiciona  valores zerados
	serie_pol[i]->AddPolar(0,0,"",clWhite);
	serie_pol[i]->Circled = true; //circular
	serie_pol[i]->Pen->Width = 2; //espessura da caneta
	serie_pol[i]->Pointer->Visible = false; //desabilita o ponteiro
	serie_pol[i]->CircleLabels = true; //exibe os labels de angulo
	serie_pol[i]->LabelsMargin = 1; //margem dos labels
	serie_pol[i]->Color=cor[i];
	serie_pol[i]->CircleGradient=dynamic_cast <TPolarSeries*>(ChartTool3->Charts->Items[0]->Chart->Series[0])->CircleGradient;
	serie_pol[i]->Shadow->Visible=false;
	serie_pol[i]->XValues->Order=loNone;
	serie_pol[i]->Pen->OwnerCriticalSection = NULL;

	serie_pol[dados.num_terminais+i] = new TPolarSeries(Chart6); //nova serie
	serie_pol[dados.num_terminais+i]->Title = (dados.pmu[i].Nome + "(C)").c_str();  //titulo da serie
  //	serie_pol[dados.num_terminais+i]->ParentChart = Chart6; //parent chart
	serie_pol[dados.num_terminais+i]->AddPolar(0,0,"",clWhite);  //adiciona  valores zerados
	serie_pol[dados.num_terminais+i]->AddPolar(0,0,"",clWhite);
	serie_pol[dados.num_terminais+i]->Circled = true; //circular
	serie_pol[dados.num_terminais+i]->Pen->Width = 2; //espessura da caneta
	serie_pol[dados.num_terminais+i]->Pointer->Visible = false; //desabilita o ponteiro
	serie_pol[dados.num_terminais+i]->CircleLabels = true; //exibe os labels de angulo
	serie_pol[dados.num_terminais+i]->LabelsMargin = 1; //margem dos labels
	serie_pol[dados.num_terminais+i]->Color=cor[dados.num_terminais+i];
	serie_pol[dados.num_terminais+i]->XValues->Order=loNone;
	serie_pol[dados.num_terminais+i]->Pen->OwnerCriticalSection = NULL;
}
Chart6->LeftAxis->Minimum = 0; //tamanho do eixo vertical
Chart6->LeftAxis->Maximum = 1;

ChartTool3->Charts->Items[0]->Chart->Title->Caption=dados.pmu[0].Nome.c_str();//o titulo é o da primeira pmu
ChartTool3->Charts->Items[0]->Chart->Title->Visible=true;

Chart6->LeftAxis->Axis->Width=1;
Chart6->BottomAxis->Axis->Width=1;
Chart6->BottomAxis->RoundFirstLabel=false;
Chart6->View3D=False;
Chart6->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
Chart6->Axes->FastCalc = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Chart6DblClick(TObject *Sender)
{
if (ChartTool2->Active) {
	ChartTool2->Active = false;
	"eu que fiz porcaria"
}
else {
    ChartTool2->Active = true;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Button1Click(TObject *Sender)
{
ChartEditor1->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->SetFocus(); //não sei porque mas se não tiver essa opção, o programa perde o foco
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
ChartTool3->Charts->Items[0]->Top=ChartTool3->Charts->Items[0]->Top+(NewHeight-this->Height);
}
//---------------------------------------------------------------------------

