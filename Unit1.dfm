object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 712
  ClientWidth = 925
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  DesignSize = (
    925
    712)
  TextHeight = 15
  object PaintBox1: TPaintBox
    Left = 24
    Top = 16
    Width = 877
    Height = 58
    OnPaint = PaintBox1Paint
  end
  object Button1: TButton
    Left = 656
    Top = 82
    Width = 73
    Height = 41
    Caption = 'Go'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 24
    Top = 136
    Width = 441
    Height = 457
    Hint = #20869#23481
    ParentShowHint = False
    ScrollBars = ssBoth
    ShowHint = True
    TabOrder = 1
    WordWrap = False
    OnChange = Memo1Change
  end
  object TreeView1: TTreeView
    Left = 492
    Top = 136
    Width = 409
    Height = 457
    Anchors = [akRight, akBottom]
    AutoExpand = True
    Indent = 19
    TabOrder = 2
    ExplicitLeft = 478
    ExplicitTop = 103
  end
  object Edit1: TEdit
    Left = 24
    Top = 91
    Width = 569
    Height = 23
    TabOrder = 3
    TextHint = #36755#20837'url'
  end
  object Button2: TButton
    Left = 686
    Top = 640
    Width = 75
    Height = 25
    Caption = 'Download'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Edit2: TEdit
    Left = 480
    Top = 641
    Width = 185
    Height = 23
    Hint = #25991#20214#21517
    TabOrder = 5
    TextHint = #20445#23384#25991#20214#21517
  end
  object ProgressBar1: TProgressBar
    Left = 32
    Top = 631
    Width = 361
    Height = 34
    TabOrder = 6
  end
  object SpinEdit1: TSpinEdit
    Left = 768
    Top = 91
    Width = 49
    Height = 24
    EditorEnabled = False
    MaxValue = 0
    MinValue = 0
    TabOrder = 7
    Value = 0
  end
  object CheckBox1: TCheckBox
    Left = 784
    Top = 644
    Width = 97
    Height = 17
    Caption = 'Continue'
    TabOrder = 8
  end
  object Edit3: TEdit
    Left = 32
    Top = 681
    Width = 201
    Height = 23
    ParentShowHint = False
    ReadOnly = True
    ShowHint = True
    TabOrder = 9
    TextHint = #24403#21069#19979#36733
  end
  object CheckBox2: TCheckBox
    Left = 840
    Top = 91
    Width = 97
    Height = 23
    Caption = 'HotKey'
    TabOrder = 10
  end
  object NetHTTPClient1: TNetHTTPClient
    UserAgent = 'Embarcadero URI Client/1.0'
    Left = 352
    Top = 632
  end
  object NetHTTPRequest1: TNetHTTPRequest
    Asynchronous = True
    Client = NetHTTPClient1
    OnRequestCompleted = NetHTTPRequest1RequestCompleted
    OnRequestError = NetHTTPRequest1RequestError
    Left = 224
    Top = 632
  end
  object NetHTTPRequest2: TNetHTTPRequest
    Asynchronous = True
    Client = NetHTTPClient2
    OnRequestCompleted = NetHTTPRequest2RequestCompleted
    OnRequestException = NetHTTPRequest2RequestException
    Left = 784
    Top = 640
  end
  object NetHTTPClient2: TNetHTTPClient
    UserAgent = 'Embarcadero URI Client/1.0'
    Left = 840
    Top = 632
  end
  object Timer1: TTimer
    Interval = 30
    OnTimer = Timer1Timer
    Left = 616
    Top = 72
  end
end
