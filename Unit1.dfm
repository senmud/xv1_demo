object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 714
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
    714)
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
    Top = 80
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
    ExplicitLeft = 482
    ExplicitTop = 118
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
    Left = 521
    Top = 675
    Width = 75
    Height = 25
    Caption = 'Download'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Edit2: TEdit
    Left = 492
    Top = 631
    Width = 269
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
    Left = 785
    Top = 638
    Width = 97
    Height = 17
    Caption = 'Continue'
    TabOrder = 8
  end
  object Edit3: TEdit
    Left = 32
    Top = 673
    Width = 361
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
  object Button3: TButton
    Left = 657
    Top = 675
    Width = 75
    Height = 25
    Caption = 'Next'
    TabOrder = 11
    OnClick = Button3Click
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
    OnRequestError = NetHTTPRequest2RequestError
    OnRequestException = NetHTTPRequest2RequestException
    Left = 768
    Top = 592
  end
  object NetHTTPClient2: TNetHTTPClient
    UserAgent = 'Embarcadero URI Client/1.0'
    Left = 832
    Top = 592
  end
  object Timer1: TTimer
    Interval = 30
    OnTimer = Timer1Timer
    Left = 616
    Top = 72
  end
end
