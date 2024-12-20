object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  BorderWidth = 5
  Caption = 'Form2'
  ClientHeight = 401
  ClientWidth = 794
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 13
  object PFormulario: TPanel
    Left = 8
    Top = 8
    Width = 313
    Height = 379
    BevelInner = bvRaised
    BorderWidth = 5
    Color = clGray
    ParentBackground = False
    TabOrder = 0
    object LCodigo: TLabel
      Left = 14
      Top = 61
      Width = 61
      Height = 23
      Caption = 'Codigo'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object LDireccion: TLabel
      Left = 14
      Top = 184
      Width = 82
      Height = 23
      Caption = 'Direccion'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object LFechaNac: TLabel
      Left = 14
      Top = 246
      Width = 179
      Height = 23
      Caption = 'Fecha de nacimiento'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object LNombre: TLabel
      Left = 14
      Top = 123
      Width = 68
      Height = 23
      Caption = 'Nombre'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object LTitle: TLabel
      Left = 38
      Top = 12
      Width = 228
      Height = 29
      Caption = 'Registro de Alumnos'
      Color = clNavy
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -24
      Font.Name = 'Trebuchet MS'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object InputCodigo: TEdit
      Left = 14
      Top = 82
      Width = 115
      Height = 27
      BevelInner = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnKeyPress = InputCodigoKeyPress
    end
    object InputNombre: TEdit
      Left = 14
      Top = 143
      Width = 251
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnKeyPress = InputNombreKeyPress
    end
    object InputDireccion: TEdit
      Left = 14
      Top = 205
      Width = 251
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object InputDia: TEdit
      Left = 16
      Top = 267
      Width = 35
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnKeyPress = InputDiaKeyPress
    end
    object InputMes: TEdit
      Left = 56
      Top = 267
      Width = 35
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnKeyPress = InputMesKeyPress
    end
    object InputAnho: TEdit
      Left = 97
      Top = 267
      Width = 56
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnKeyPress = InputAnhoKeyPress
    end
    object BtnGuardar: TButton
      Left = 16
      Top = 328
      Width = 99
      Height = 25
      Caption = 'Guardar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = OnGuardarRegistro
    end
    object BtnLimpiar: TButton
      Left = 175
      Top = 328
      Width = 90
      Height = 25
      Caption = 'Limpiar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      OnClick = OnLimpiarForm
    end
  end
  object PListado: TPanel
    Left = 328
    Top = 8
    Width = 458
    Height = 379
    Color = clGray
    ParentBackground = False
    TabOrder = 1
    object ListaNombre: TLabel
      Left = 16
      Top = 117
      Width = 425
      Height = 35
      AutoSize = False
      Caption = 'Nombre'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = False
      Layout = tlCenter
    end
    object ListaCodigo: TLabel
      Left = 16
      Top = 61
      Width = 89
      Height = 35
      AutoSize = False
      Caption = 'Codigo'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = False
      Layout = tlCenter
    end
    object ListaDireccion: TLabel
      Left = 16
      Top = 170
      Width = 425
      Height = 35
      AutoSize = False
      Caption = 'Direccion'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = False
      Layout = tlCenter
    end
    object ListaFechNac: TLabel
      Left = 16
      Top = 222
      Width = 425
      Height = 35
      AutoSize = False
      Caption = 'Fecha de naciemiento'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = False
      Layout = tlCenter
    end
    object BtnFinNavegacion: TButton
      Left = 328
      Top = 19
      Width = 113
      Height = 25
      Caption = 'Finalizar Navegacion'
      Enabled = False
      TabOrder = 0
      OnClick = OnEndNavegacion
    end
    object BtnNextRegistro: TButton
      Left = 367
      Top = 270
      Width = 75
      Height = 25
      Caption = '>>'
      Enabled = False
      TabOrder = 1
      OnClick = OnNextRegistro
    end
    object BtnPrevRegistro: TButton
      Left = 16
      Top = 270
      Width = 75
      Height = 25
      Caption = '<<'
      Enabled = False
      TabOrder = 2
      OnClick = OnPreviosRegistro
    end
    object Button3: TButton
      Left = 16
      Top = 328
      Width = 99
      Height = 25
      Caption = 'Editar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = OnEditarRegistro
    end
    object Button1: TButton
      Left = 351
      Top = 328
      Width = 90
      Height = 25
      Caption = 'Eliminar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = OnEliminarRegistro
    end
    object ComBoNavegacion: TComboBox
      Left = 16
      Top = 19
      Width = 145
      Height = 21
      TabOrder = 5
      Text = 'Navegar Por?'
      OnChange = OnChangeNavegacion
    end
  end
  object MainMenu1: TMainMenu
    Left = 65528
    Top = 65528
    object Indices1: TMenuItem
      Caption = 'Indices'
      object porcodigo1: TMenuItem
        Caption = 'por codigo'
        OnClick = CrearIndicePorCodigoClick
      end
      object pornombre1: TMenuItem
        Caption = 'por nombre'
        OnClick = CrearIndicePorNombreClick
      end
    end
    object Ordenar1: TMenuItem
      Caption = 'Ordenar'
      object Porcodigo2: TMenuItem
        Caption = 'Por codigo'
        OnClick = OrdenarPorCodigoClick
      end
      object Pornombre2: TMenuItem
        Caption = 'Por nombre'
        OnClick = OrdenarPorNombreClick
      end
    end
  end
end
