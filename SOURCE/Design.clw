; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHelp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Design.h"

ClassCount=17
Class1=CDesignApp
Class2=CDesignDlg
Class3=CAboutDlg

ResourceCount=19
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DEPEND_OF_X_DIALOG
Class4=CBagOfX
Resource4=IDD_UPDATEDBDLG_DIALOG
Class5=CDepend
Resource5=IDD_NODE_ARG_DIALOG
Class6=CViewD
Resource6=IDD_VIEW_D_FULL_DIALOG
Class7=CDisR
Resource7=IDR_DESIGN_ACCELERATOR
Resource8=IDD_GRAPH_DIALOG
Class8=CHelp
Resource9=IDR_DESIGN_MENU
Class9=CPtt
Resource10=IDD_MINI_DIALOG
Class10=CMini
Resource11=IDD_DIS_DIALOG
Class11=CViewColl
Resource12=IDD_HELP_DIALOG
Resource13=IDD_BAG_OF_X_DIALOG
Class12=CGraph
Resource14=IDD_PERFORM_DIALOG
Class13=CPerform
Resource15=IDD_CHOOSE_DIALOG
Class14=CChoose
Resource16=IDD_DESIGN_DIALOG
Class15=CNodeArg
Resource17=IDD_PTT_DIALOG
Class16=CABC
Resource18=IDD_VIEW_COLLECT_FULL_DIALOG
Class17=CUpdateDBDlg
Resource19=IDD_GRAPH_HELP_DIALOG

[CLS:CDesignApp]
Type=0
HeaderFile=Design.h
ImplementationFile=Design.cpp
Filter=N

[CLS:CDesignDlg]
Type=0
HeaderFile=DesignDlg.h
ImplementationFile=DesignDlg.cpp
Filter=D
LastObject=IDC_GRAPH_BUTTON
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DesignDlg.h
ImplementationFile=DesignDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DESIGN_DIALOG]
Type=1
Class=CDesignDlg
ControlCount=33
Control1=IDC_R_EDIT,edit,1350631552
Control2=IDC_D_EDIT,edit,1353781444
Control3=IDC_ACCEPT_BUTTON,button,1342242816
Control4=IDC_CLEAR_BUTTON,button,1342242816
Control5=IDC_PTT_BUTTON,button,1342242816
Control6=IDC_FIND_KEY_BUTTON,button,1342242816
Control7=IDC_BAG_OF_X_BUTTON,button,1342242816
Control8=IDC_CO_SO_TT_BUTTON,button,1342242816
Control9=IDC_DEPEND_OF_X_BUTTON,button,1342242816
Control10=IDC_DIS_RELATE_BUTTON,button,1342242816
Control11=IDC_COLLECT_BUTTON,button,1342242816
Control12=IDC_DIS_RELATE_ENHANCED_BUTTON,button,1342242816
Control13=IDC_GRAPH_BUTTON,button,1342242816
Control14=IDOK,button,1342242817
Control15=IDC_KEY_EDIT,edit,1350633600
Control16=IDC_BAG_OF_X_EDIT,edit,1350633600
Control17=IDC_BX_EDIT,edit,1350633600
Control18=IDC_DEPEND_OF_X_EDIT,edit,1350633600
Control19=IDC_DX_EDIT,edit,1350633600
Control20=IDC_DIS_RELATE_EDIT,edit,1350633600
Control21=IDC_VIEW_D_FULL_BUTTON,button,1342242816
Control22=IDC_COLLECT_EDIT,edit,1350633600
Control23=IDC_VIEW_COLLECT_FULL_BUTTON,button,1342242816
Control24=IDC_STATIC,static,1342308864
Control25=IDC_STATIC,static,1342308864
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308864
Control31=IDC_STATIC,static,1342308864
Control32=IDC_KEY_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352

[CLS:CBagOfX]
Type=0
HeaderFile=BagOfX.h
ImplementationFile=BagOfX.cpp
BaseClass=CDialog
Filter=D
LastObject=CBagOfX
VirtualFilter=dWC

[DLG:IDD_BAG_OF_X_DIALOG]
Type=1
Class=CBagOfX
ControlCount=5
Control1=IDC_X_EDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DEPEND_OF_X_DIALOG]
Type=1
Class=CDepend
ControlCount=5
Control1=IDC_X_EDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CDepend]
Type=0
HeaderFile=Depend.h
ImplementationFile=Depend.cpp
BaseClass=CDialog
Filter=D
LastObject=CDepend
VirtualFilter=dWC

[CLS:CViewD]
Type=0
HeaderFile=ViewD.h
ImplementationFile=ViewD.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FIND_KEY_BUTTON
VirtualFilter=dWC

[DLG:IDD_VIEW_D_FULL_DIALOG]
Type=1
Class=CViewD
ControlCount=8
Control1=IDC_PERFORM_BUTTON,button,1342242817
Control2=IDOK,button,1342242817
Control3=IDC_FIND_KEY_BUTTON,button,1342242817
Control4=IDC_KEY_EDIT,edit,1350633600
Control5=IDC_KEY_STATIC,static,1342308352
Control6=IDC_VIEW_D_FULL_EDIT,edit,1353783492
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DIS_DIALOG]
Type=1
Class=CDisR
ControlCount=6
Control1=IDC_VALUE_COMBO,combobox,1344340035
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDisR]
Type=0
HeaderFile=DisR.h
ImplementationFile=DisR.cpp
BaseClass=CDialog
Filter=D
LastObject=CDisR
VirtualFilter=dWC

[MNU:IDR_DESIGN_MENU]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVEAS
Command5=ID_FILE_EXIT
Command6=ID_CONTEXT_HELP
Command7=ID_APP_ABOUT
CommandCount=7

[DLG:IDD_HELP_DIALOG]
Type=1
Class=CHelp
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HELP_EDIT,edit,1352734788
Control5=IDC_STATIC,static,1342308352

[CLS:CHelp]
Type=0
HeaderFile=Help.h
ImplementationFile=Help.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelp
VirtualFilter=dWC

[DLG:IDD_PTT_DIALOG]
Type=1
Class=CPtt
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_PTT_LIST,listbox,1352728833

[CLS:CPtt]
Type=0
HeaderFile=Ptt.h
ImplementationFile=Ptt.cpp
BaseClass=CDialog
Filter=D
LastObject=CPtt
VirtualFilter=dWC

[DLG:IDD_MINI_DIALOG]
Type=1
Class=CMini
ControlCount=8
Control1=IDC_SOURCE_EDIT,edit,1350631552
Control2=IDC_DEST_EDIT,edit,1350633600
Control3=IDC_AGREE_BUTTON,button,1342242817
Control4=IDC_DEL_BUTTON,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CMini]
Type=0
HeaderFile=Mini.h
ImplementationFile=Mini.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_AGREE_BUTTON

[CLS:CViewColl]
Type=0
HeaderFile=ViewColl.h
ImplementationFile=ViewColl.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FIND_KEY_BUTTON
VirtualFilter=dWC

[DLG:IDD_VIEW_COLLECT_FULL_DIALOG]
Type=1
Class=CViewColl
ControlCount=8
Control1=IDC_PERFORM_BUTTON,button,1342242817
Control2=IDC_FIND_KEY_BUTTON,button,1342242817
Control3=IDOK,button,1342242817
Control4=IDC_KEY_EDIT,edit,1350633600
Control5=IDC_KEY_STATIC,static,1342308352
Control6=IDC_VIEW_COLLECT_FULL_EDIT,edit,1353783492
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[ACL:IDR_DESIGN_ACCELERATOR]
Type=1
Class=CDesignDlg
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
CommandCount=3

[DLG:IDD_GRAPH_DIALOG]
Type=1
Class=CGraph
ControlCount=11
Control1=IDC_ACCEPT_BUTTON,button,1342242816
Control2=IDC_CLEAR_BUTTON,button,1476460544
Control3=IDC_PERFORM_BUTTON,button,1476460544
Control4=IDC_TABLEAU_BUTTON,button,1476460544
Control5=IDC_FIND_KEY_BUTTON,button,1476460545
Control6=IDC_KEY_EDIT,edit,1350633600
Control7=IDCANCEL,button,1342242816
Control8=IDC_ENTER_EDIT,edit,1353781444
Control9=IDC_STATIC,static,1342308352
Control10=IDC_KEY_STATIC,static,1342308352
Control11=IDC_LINEARD_BUTTON,button,1476460544

[CLS:CGraph]
Type=0
HeaderFile=Graph.h
ImplementationFile=Graph.cpp
BaseClass=CDialog
Filter=D
LastObject=CGraph
VirtualFilter=dWC

[CLS:CPerform]
Type=0
HeaderFile=Perform.h
ImplementationFile=Perform.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_GRAPH_MSFLEXGRID
VirtualFilter=dWC

[DLG:IDD_PERFORM_DIALOG]
Type=1
Class=CPerform
ControlCount=14
Control1=IDC_GRAPH_MSFLEXGRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control2=IDC_VIEW_FULL_BUTTON,button,1342242817
Control3=IDOK,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177287
Control6=IDC_NODE_I_STATIC,static,1342308352
Control7=IDC_NODE_I_EDIT,edit,1350633600
Control8=IDC_ARG_I_STATIC,static,1342308352
Control9=IDC_ARG_I_EDIT,edit,1350633600
Control10=IDC_NODE_J_STATIC,static,1342308352
Control11=IDC_NODE_J_EDIT,edit,1350633600
Control12=IDC_ARG_J_STATIC,static,1342308352
Control13=IDC_ARG_J_EDIT,edit,1350633600
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_CHOOSE_DIALOG]
Type=1
Class=CChoose
ControlCount=5
Control1=IDC_VALUE_COMBO,combobox,1344340227
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CChoose]
Type=0
HeaderFile=Choose.h
ImplementationFile=Choose.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChoose

[DLG:IDD_NODE_ARG_DIALOG]
Type=1
Class=CNodeArg
ControlCount=19
Control1=IDC_FIND_KEY_NODE_BUTTON,button,1342242817
Control2=IDC_KEY_NODE_EDIT,edit,1350633600
Control3=IDC_FIND_KEY_ARG_BUTTON,button,1342242817
Control4=IDC_KEY_ARG_EDIT,edit,1350633600
Control5=IDC_FIND_KEY_Qo_BUTTON,button,1342242817
Control6=IDOK,button,1342242817
Control7=IDC_NODE_EDIT,edit,1353783492
Control8=IDC_ARG_EDIT,edit,1353783492
Control9=IDC_STATIC,static,1342308352
Control10=IDC_KEY_NODE_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_KEY_ARG_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_Qo_EDIT,edit,1350633600
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_KEY_Qo_EDIT,edit,1350633600
Control19=IDC_KEY_Qo_STATIC,static,1342308352

[CLS:CNodeArg]
Type=0
HeaderFile=NodeArg.h
ImplementationFile=NodeArg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNodeArg
VirtualFilter=dWC

[DLG:IDD_GRAPH_HELP_DIALOG]
Type=1
Class=CABC
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_HELP_EDIT,edit,1352734788

[CLS:CABC]
Type=0
HeaderFile=ABC.h
ImplementationFile=ABC.cpp
BaseClass=CDialog
Filter=D
LastObject=CABC

[DLG:IDD_UPDATEDBDLG_DIALOG]
Type=1
Class=CUpdateDBDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CUpdateDBDlg]
Type=0
HeaderFile=UpdateDBDlg.h
ImplementationFile=UpdateDBDlg.cpp
BaseClass=CDialog
Filter=D

