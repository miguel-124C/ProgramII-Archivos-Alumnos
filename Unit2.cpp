//---------------------------------------------------------------------------

#include <vcl.h>

#include <iostream>
#include <string>


#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{ }
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	nomArch="Alumnos.dat";
	nomIdxCod="codi.idx";

	TextButton = "Guardar";
    Editar = false;
   pf=new fstream(nomArch.c_str(),ios::in|ios::binary);
   if (pf-> fail()) {
	   delete(pf);
	   pf = new fstream(nomArch.c_str(),ios::out|ios::binary);
   }
   pf->close();
   delete(pf);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
  /*	  pf->flush();
	  pf->close();
	  delete pf;  */
}

void TForm2::LimpiarFormulario(){
	InputCodigo->Text = "";
	InputNombre->Text = "";
	InputDireccion->Text = "";
	InputDia->Text = "";
	InputMes->Text = "";
	InputAnho->Text = "";
}

void TForm2::LimpiarListado(){
	ListaCodigo->Caption 	= "";
	ListaNombre->Caption 	= "";
	ListaDireccion->Caption = "";
	ListaFechNac->Caption 	= "";
}

void TForm2::SetRegistroEnLista( RegAlumno registro ){
	ListaCodigo->Caption 	= registro.cod;
	ListaNombre->Caption 	= registro.nom;
	ListaDireccion->Caption = registro.dir;
	ListaFechNac->Caption 	= AnsiString(registro.fecha.dia) + "/" + registro.fecha.mes + "/" + registro.fecha.a�o;
}

void TForm2::SetRegistroEnForm( RegAlumno registro ){
	InputCodigo->Text 	= registro.cod;
	InputNombre->Text 	= registro.nom;
	InputDireccion->Text = registro.dir;
	InputDia->Text 	= registro.fecha.dia;
	InputMes->Text = registro.fecha.mes;
    InputAnho->Text = registro.fecha.a�o;
}

void TForm2::SetEnabledInputs( bool isEnable ){
	InputCodigo->Enabled = isEnable;
	InputNombre->Enabled = isEnable;
	InputDireccion->Enabled = isEnable;
	InputDia->Enabled = isEnable;
	InputMes->Enabled = isEnable;
	InputAnho->Enabled = isEnable;
	BtnLimpiar->Enabled = isEnable;
   	BtnGuardar->Enabled = isEnable;
}


//-----------------------------EVENTOS---------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::OnGuardarRegistro(TObject *Sender)
{
	bool hallado= false;
	AnsiString cad;
	RegAlumno reg,regNuevo;

	regNuevo.mark='0';//no marcado para borrar
	regNuevo.cod=StrToInt(InputCodigo->Text);
	cad=InputNombre->Text;
	strcpy(regNuevo.nom,cad.c_str());
	cad=InputDireccion->Text;
	strcpy(regNuevo.dir,cad.c_str());

	regNuevo.fecha.dia=StrToInt(InputDia->Text);
	regNuevo.fecha.mes=StrToInt(InputMes->Text);
	regNuevo.fecha.a�o=StrToInt(InputAnho->Text);
	pf = new fstream(nomArch.c_str(),ios::in|ios::out|ios::binary);

	if (pf->is_open()) {
		do{
			pf->read((char *)&reg,sizeof(reg));
		 	hallado=(reg.cod==regNuevo.cod)&&(reg.mark!='*');
		}while(!hallado && !pf->eof());

        if( Editar ){

		}else{
			if (!hallado) {
                pf->seekg(0,ios::end);
				pf->write((char *)&regNuevo,sizeof(regNuevo));
				LimpiarFormulario();
				InputCodigo->SetFocus();
				pf->close();
			}else{
				AnsiString codigo = regNuevo.cod;
				ShowMessage( "El alumno con el c�digo: " + codigo + " ya existe" );
			}
		}
	}
	pf->flush();
	delete(pf);
}

//---------------------------------------------------------------------------
void __fastcall TForm2::OnEliminarRegistro(TObject *Sender)
{
	bool hallado=false;
	RegAlumno reg;
	Word cod;
	reg.mark='0';
	cod=StrToInt(ListaCodigo->Caption);
	pf=new fstream(nomArch.c_str(),ios::in|ios::out|ios::binary);

	if (pf->is_open()) {
		do{
		  pf->read((char*)&reg,sizeof(reg));
		  hallado=(reg.cod==cod)&&(reg.mark!='*');
		}while(!hallado && !pf->eof());

		if (hallado){
			reg.mark='*';
			pf->seekg(-sizeof(reg),ios::cur);
			pf->write((char *)&reg,sizeof(reg));
			LimpiarFormulario();
		}
	}
   pf->close();
   delete(pf);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BtnNavegarClick(TObject *Sender)
{
	RegIdxCod regIdx;
	RegAlumno regA;
	pf=new fstream(nomArch.c_str(),ios::in|ios::binary);
	pIdx =new fstream(nomIdxCod.c_str(),ios::in|ios::binary);
	if (pIdx->is_open()) {
		pIdx->read((char*)&regIdx,sizeof(regIdx));
		if (!pIdx->eof()) {
			pf->seekp(regIdx.pos,ios::beg);
			pf->read((char*)&regA,sizeof(regA));

			if( regA.mark != '*' ){
				SetRegistroEnLista( regA );
                BtnPrevRegistro->Enabled=true;
				BtnNextRegistro->Enabled=true;
				BtnFinNavegacion->Enabled=true;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::onEndNavegacion(TObject *Sender)
{
    pf->close();
	pIdx->close();
	delete(pf);
	delete(pIdx);
	BtnPrevRegistro->Enabled=false;
	BtnNextRegistro->Enabled=false;
	BtnFinNavegacion->Enabled=false;
    LimpiarListado();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::onNextRegistro(TObject *Sender)
{
 RegIdxCod reg;
  RegAlumno regA;
  if (pIdx->is_open()) {
	  pIdx->read((char*)&reg,sizeof(reg));
	  if (!pIdx->eof()) {
		  pf->seekp(reg.pos,ios::beg);
		  pf->read((char *)&regA,sizeof (regA));
		  SetRegistroEnLista( regA );
		  BtnPrevRegistro->Enabled=true;
	  } else {
		 pIdx->close();
		 delete(pIdx);
		 pIdx=new fstream(nomIdxCod.c_str(),ios::in|ios::binary);
		 pIdx->seekp(0,ios::end);
		 BtnNextRegistro->Enabled=false;
		 BtnPrevRegistro->Enabled=true;
	  }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BtnPrevRegistroClick(TObject *Sender)
{
	RegIdxCod reg;
	RegAlumno regA;
	Cardinal p;
	if (pIdx->is_open()) {
		p=pIdx->tellp();
	if (p<=sizeof(reg)){ //si est� en el primer registro del idx
	  BtnPrevRegistro->Enabled=false;
	}else {
	  pIdx->seekp(-2*sizeof(reg),ios::cur);
	  pIdx->read((char*)&reg,sizeof(reg));
	  if (!pIdx->eof()) {
		  pf->seekp(reg.pos,ios::beg);
		  pf->read((char *)&regA,sizeof(regA));
		  SetRegistroEnLista(regA);
		  BtnPrevRegistro->Enabled=true;
   		  BtnNextRegistro->Enabled=true;
	  }
	}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CrearIndicePorCodigoClick(TObject *Sender)
{
	RegAlumno reg;
	RegIdxCod regIdx;
	fstream pix(nomIdxCod.c_str(),ios::out|ios::trunc|ios::binary);
    pf = new fstream(nomArch.c_str(), ios::in | ios::binary);
	do{
		 regIdx.pos=pf->tellp();
		 pf->read((char *)&reg,sizeof(reg));
		 if (!pf->fail())  {
			regIdx.cod=reg.cod;
			pix.write((char *)&regIdx,sizeof(regIdx));

		 }
	}while(!pf->eof());

    pix.flush();
	pf->close();
	pix.close();
	delete(pf);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OrdenarPorCodigoClick(TObject *Sender)
{
fstream f(nomIdxCod.c_str(),ios::in|ios::out|ios::binary);
  RegIdxCod reg,regM;
  bool fin=false;
  Cardinal p,i,pm,z;
  if (f.is_open()) {
	p=0;
	while (!fin){
	  i=0; pm=p;
	  f.seekg(p);//,ios::beg);//al inicio del archivo
	  while (!f.eof()){ //busca el menor
		 if (p==f.tellp()){//si es el primer registro
			f.read((char *)&reg,sizeof(reg));
			regM=reg;
			z=f.tellp();
		 } else {
			f.read((char *)&reg,sizeof(reg));
			z=f.tellp();
		 }
		 if (!f.eof()) {
			i++;
			if (reg.cod<regM.cod) {
			   regM=reg;
			   pm=f.tellp()-sizeof(reg);
			}
		 }
	  }
	  fin= i<=1;
	  if (!fin) {
		  //f.flush();
		  f.close();
		  f.open(nomIdxCod.c_str(),ios::in|ios::out|ios::binary);
		//if (p!=pm){
		  f.seekg(p);
		  f.seekp(p);
		  z=f.tellp();  //intercambia el menor con el de la pos.p
		  f.read((char *)&reg,sizeof(reg));
		  z=f.tellp();
		  f.seekp(p);//,ios::beg);
		  z=f.tellp();
		  f.write((char *)&regM,sizeof(reg));
		  z=f.tellp();
		  f.seekp(pm);//,ios::beg);
		  z=f.tellp();
		  f.write((char *)&reg,sizeof(reg));
		  z=f.tellp();
	  }
	  p=p+sizeof(reg);
	}
  }
	f.flush();
	f.close();
}
//--------------------------------------------------------------------------
void __fastcall TForm2::OnEditarRegistro(TObject *Sender)
{
	Word codigo = StrToInt(ListaCodigo->Caption);
	RegAlumno reg;

    pf = new fstream( nomArch.c_str(), ios::in | ios::binary );
	if( pf->is_open() ){
		do{
			pf->read( (char*)&reg, sizeof(reg) );

			if( reg.cod == codigo ){
                SetRegistroEnForm( reg );
                break;
			}

		}while( !pf->eof() );
	}
	pf->flush();
	delete(pf);
}






void __fastcall TForm2::OnLimpiarForm(TObject *Sender){
	LimpiarFormulario();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::InputCodigoKeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((Key>=32&& Key<=47)||(Key>=58 && Key<=255)) {
		 ShowMessage("ERROR SOLO DEBE INTRODUCIR NUMEROS");
		 Key=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::InputNombreKeyPress(TObject *Sender, System::WideChar &Key)
{
	 if ((Key>=33 && Key<=64)||(Key>=91 && Key<=96)||(Key>=123 && Key<=255)) {
		  ShowMessage("ERROR SOLO DEBEN INTRODUCIR LETRAS");
		  Key=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::InputDiaKeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((Key>=33&& Key<=47)||(Key>=58 && Key<=255)) {
		 ShowMessage("ERROR SOLO DEBE INTRODUCIR NUMEROS");
		 Key=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::InputMesKeyPress(TObject *Sender, System::WideChar &Key)
{
		if ((Key>=33&& Key<=47)||(Key>=58 && Key<=255)) {

		 ShowMessage("ERROR SOLO DEBE INTRODUCIR NUMEROS");
		 Key=0;
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm2::InputAnhoKeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((Key>=33&& Key<=47)||(Key>=58 && Key<=255)) {

		 ShowMessage("ERROR SOLO DEBE INTRODUCIR NUMEROS");
		 Key=0;
	}
}