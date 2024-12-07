//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <FStream>
//---------------------------------------------------------------------------
struct TFecha{
	byte dia;
	byte mes;
	Word año;
};
struct RegAlumno{
	char mark; //marca de borrador
	Word cod;
	char nom[21];//cadena de 20 caracteres
	char dir[21];  //cadena de 20 caracteres
	TFecha fecha;
};
struct RegIdxCod{
	Word cod;  //codigo del alumno
	Cardinal pos; //posicion de archivos de daots de alumnos
};

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *LTitle;
	TLabel *LCodigo;
	TLabel *LNombre;
	TLabel *LDireccion;
	TLabel *LFechaNac;
	TButton *BtnGuardar;
	TButton *BtnLimpiar;
	TEdit *InputCodigo;
	TEdit *InputNombre;
	TEdit *InputDireccion;
	TEdit *InputDia;
	TEdit *InputMes;
	TEdit *InputAnho;
	TMainMenu *MainMenu1;
	TMenuItem *Indices1;
	TMenuItem *porcodigo1;
	TMenuItem *pornombre1;
	TButton *BtnNavegar;
	TButton *BtnPrevRegistro;
	TButton *BtnNextRegistro;
	TButton *BtnFinNavegacion;
	TMenuItem *Ordenar1;
	TMenuItem *Porcodigo2;
	TMenuItem *Pornombre2;
	TPanel *PFormulario;
	TPanel *PListado;
	TLabel *ListaNombre;
	TLabel *ListaCodigo;
	TLabel *ListaDireccion;
	TLabel *ListaFechNac;
	TButton *Button3;
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall InputCodigoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall InputNombreKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall InputDiaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall InputMesKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall InputAnhoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall OnGuardarRegistro(TObject *Sender);
	void __fastcall OnEliminarRegistro(TObject *Sender);
	void __fastcall CrearIndicePorCodigoClick(TObject *Sender);
	void __fastcall BtnNavegarClick(TObject *Sender);
	void __fastcall onEndNavegacion(TObject *Sender);
	void __fastcall onNextRegistro(TObject *Sender);
	void __fastcall BtnPrevRegistroClick(TObject *Sender);
	void __fastcall OrdenarPorCodigoClick(TObject *Sender);
	void __fastcall OnLimpiarForm(TObject *Sender);
	void __fastcall OnEditarRegistro(TObject *Sender);
private:	// User declarations
   fstream *pf,*pIdx;
   AnsiString nomArch,nomIdxCod;
   AnsiString TextButton;
   bool Editar;
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	void LimpiarFormulario();
	void LimpiarListado();
	void SetRegistroEnLista( RegAlumno registro );
	void SetEnabledInputs( bool isEnable );

	void SetRegistroEnForm( RegAlumno registro );
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------

#endif
