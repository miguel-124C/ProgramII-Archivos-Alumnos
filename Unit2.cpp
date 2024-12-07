//---------------------------------------------------------------------------

#include <vcl.h>

#include <Vcl.Dialogs.hpp>
#include <iostream>
#include <string>
#include <cstring>

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
    nombreIdxNombre = "nombrei.idx";

	BtnGuardar->Caption = "Guardar";

	itemsNavegacion.push_back("Codigo");
	itemsNavegacion.push_back("Nombre");
    SetItemsComboNavegacion();
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

void TForm2::SetItemsComboNavegacion(){
    short i;
	for (i = 0; i < itemsNavegacion.size(); i++) {
		ComBoNavegacion->Items->Add( itemsNavegacion.at(i) );
	}
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
	ListaFechNac->Caption 	= AnsiString(registro.fecha.dia) + "/" + registro.fecha.mes + "/" + registro.fecha.año;
}

void TForm2::SetRegistroEnForm( RegAlumno registro ){
	InputCodigo->Text 	= registro.cod;
	InputNombre->Text 	= registro.nom;
	InputDireccion->Text = registro.dir;
	InputDia->Text 	= registro.fecha.dia;
	InputMes->Text = registro.fecha.mes;
    InputAnho->Text = registro.fecha.año;
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
	regNuevo.fecha.año=StrToInt(InputAnho->Text);
	pf = new fstream(nomArch.c_str(),ios::in|ios::out|ios::binary);

	if (pf->is_open()) {
		do{
			pf->read((char *)&reg,sizeof(reg));
		 	hallado=(reg.cod==regNuevo.cod)&&(reg.mark!='*');
		}while(!hallado && !pf->eof());

        if( Editar ){
			pf->seekg(-sizeof(reg),ios::cur); // ios::cur   pone el puntero en el actual menos el tamaño del registro
			pf->write((char *)&regNuevo,sizeof(regNuevo));
			ShowMessage("Editado con exito");
			BtnGuardar->Caption = "Guardar";
		}else{
			if (!hallado) {
				pf->seekg(0,ios::end);
				pf->write((char *)&regNuevo,sizeof(regNuevo));
			}else{
				AnsiString codigo = regNuevo.cod;
				ShowMessage( "El alumno con el código: " + codigo + " ya existe" );
			}
		}
        LimpiarFormulario();
		InputCodigo->SetFocus();
		pf->close();
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
	cod = StrToInt(ListaCodigo->Caption);
	pf=new fstream(nomArch.c_str(),ios::in|ios::out|ios::binary);

	if (pf->is_open()) {
		AnsiString question = "¿Estás seguro de eliminar este Alumno?";
		int respuesta = MessageDlg(question, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);

		if( respuesta == mrYes ){
			do{
			  pf->read((char*)&reg,sizeof(reg));
			  hallado=(reg.cod==cod)&&(reg.mark!='*');
			}while(!hallado && !pf->eof());

			if (hallado){
				reg.mark='*';
				pf->seekg(-sizeof(reg),ios::cur);
				pf->write((char *)&reg,sizeof(reg));
				LimpiarFormulario();
                ShowMessage("Alumno Eliminado Con Exito");
			}
		}
	}
   pf->close();
   delete(pf);
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
				Editar = true;
                BtnGuardar->Caption = "Editar";
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



//---------------------------------------------------------------------------
//------------------------------INDICES--------------------------------------
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
void __fastcall TForm2::CrearIndicePorNombreClick(TObject *Sender)
{
	RegAlumno regAlumno;
	RegIdxNombre regIdxNombre;
	fstream fileIdxNombre( nombreIdxNombre.c_str(), ios::out | ios::trunc | ios::binary );
    pf = new fstream(nomArch.c_str(), ios::in | ios::binary);

	do{
		regIdxNombre.pos = pf->tellp();
		pf->read( (char*)&regAlumno, sizeof(regAlumno) );
		if( !pf->fail() ){
			strncpy(regIdxNombre.nombre, regAlumno.nom, sizeof(regIdxNombre.nombre) - 1);
			regIdxNombre.nombre[sizeof(regIdxNombre.nombre) - 1] = '\0';  // Asegurarse de que se termine con '\0'

			fileIdxNombre.write( (char*)&regIdxNombre, sizeof(regIdxNombre) );
		}
	}while( !pf->eof() );
	fileIdxNombre.flush();
	pf->close();
	fileIdxNombre.close();
	delete(pf);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//------------------------ORDENAR INDICES------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::OrdenarPorCodigoClick(TObject *Sender)
{
	fstream f(nomIdxCod.c_str(),ios::in|ios::out|ios::binary);
	RegIdxCod reg,regM;
	bool fin=false;
	Cardinal p,i,punteroMenor,z;
	if (f.is_open()) {
		p=0;
		while (!fin){
		  i=0; punteroMenor=p;
		  f.seekg(p);
		  while (!f.eof()){ //busca el menor
			 if ( p == f.tellp() ){//si es el primer registro
                f.read((char *)&reg,sizeof(reg));
				regM=reg;
			 }else{
                f.read((char *)&reg,sizeof(reg));
			 }

			 z=f.tellp();

			 if (!f.eof()) {
				i++;
				if (reg.cod<regM.cod) {
				   regM = reg;
				   punteroMenor = z - sizeof(reg);
				}
			 }
		  }
		  fin= i<=1;
		  if (!fin) {
			f.close();
			f.open(nomIdxCod.c_str(),ios::in|ios::out|ios::binary);
			f.seekg(p);
			f.seekp(p);
			f.read((char *)&reg,sizeof(reg));
			f.seekp(p);
			f.write((char *)&regM,sizeof(reg));
			f.seekp(punteroMenor);
			f.write((char *)&reg,sizeof(reg));
		  }
		  p = p + sizeof(reg);
		}
	}
	f.flush();
	f.close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OrdenarPorNombreClick(TObject *Sender)
{
	fstream file(nombreIdxNombre.c_str(),ios::in|ios::out|ios::binary);
	RegIdxNombre reg,regM;
	bool fin=false;
	Cardinal p,i,punteroMenor,z;
	if (file.is_open()) {
		p=0;
		while (!fin){
		  i=0; punteroMenor=p;
		  file.seekg(p);
		  while (!file.eof()){ //busca el menor
			 if ( p == file.tellp() ){//si es el primer registro
				file.read((char *)&reg,sizeof(reg));
				regM=reg;
			 }else{
                file.read((char *)&reg,sizeof(reg));
			 }

			 z=file.tellp();

			 if (!file.eof()) {
				i++;
				int esMenor = strcmp(reg.nombre, regM.nombre);
				if ( esMenor < 0 ) {
				   regM = reg;
				   punteroMenor = z - sizeof(reg);
				}
			 }
		  }
		  fin= i<=1;
		  if (!fin) {
			file.close();
			file.open(nombreIdxNombre.c_str(),ios::in|ios::out|ios::binary);
			file.seekg(p);
			file.seekp(p);
			file.read((char *)&reg,sizeof(reg));
			file.seekp(p);
			file.write((char *)&regM,sizeof(reg));
			file.seekp(punteroMenor);
			file.write((char *)&reg,sizeof(reg));
		  }
		  p = p + sizeof(reg);
		}
	}
	file.flush();
	file.close();
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
//----------------------------NAVEGACION-------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::OnChangeNavegacion(TObject *Sender)
{
	short i;
	short indice;
	for (i = 0; i < itemsNavegacion.size(); i++) {
		if(ComBoNavegacion->Text == itemsNavegacion.at(i)){
			indice = i;
			break;
		}
	}

	switch (indice) {
		case 0: {
			OnIniciarNavegacion();
			break;
		}
		case 1: {
			OnIniciarNavegacionPorNombre();
			break;
		}
		default: {
			OnIniciarNavegacion();
            break;
		}
	}
}
//---------------------------------------------------------------------------
void TForm2::OnIniciarNavegacion()
{
    RegIdxCod reg;
	RegAlumno regA;
	pf=new fstream(nomArch.c_str(),ios::in|ios::binary);
	pIdx =new fstream(nomIdxCod.c_str(),ios::in|ios::binary);
	if (pIdx->is_open()) {
		pIdx->read((char*)&reg,sizeof(reg));
		if (!pIdx->eof()) {
			pf->seekp(reg.pos,ios::beg);
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
void __fastcall TForm2::OnEndNavegacion(TObject *Sender)
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
//---------------------BOTONES DE NAVEGACION---------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::OnNextRegistro(TObject *Sender)
{
 RegIdxNombre reg;
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
		 pIdx=new fstream(nombreIdxNombre.c_str(),ios::in|ios::binary);
		 pIdx->seekp(0,ios::end);
		 BtnNextRegistro->Enabled=false;
		 BtnPrevRegistro->Enabled=true;
	  }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OnPreviosRegistro(TObject *Sender)
{
	RegIdxNombre reg;
	RegAlumno regA;
	Cardinal p;
	if (pIdx->is_open()) {
		p=pIdx->tellp();
	if (p<=sizeof(reg)){ //si está en el primer registro del idx
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
void TForm2::OnIniciarNavegacionPorNombre()
{
    RegIdxNombre reg;
	RegAlumno regA;
	pf=new fstream(nomArch.c_str(),ios::in|ios::binary);
	pIdx =new fstream(nombreIdxNombre.c_str(),ios::in|ios::binary);
	if (pIdx->is_open()) {
		pIdx->read((char*)&reg,sizeof(reg));
		if (!pIdx->eof()) {
			pf->seekp(reg.pos,ios::beg);
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

