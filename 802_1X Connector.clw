; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProPage1
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "802_1x connector.h"
LastPage=0

ClassCount=8
Class1=CMy802_1XConnectorApp
Class2=CAboutDlg
Class3=CMy802_1XConnectorDlg
Class4=CChooseCard
Class5=CProPage1
Class6=CProPage2
Class7=CProPage3
Class8=CProSheet

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG1
Resource3=IDD_PROPPAGE_LARGE1
Resource4=IDD_MY802_1XCONNECTOR_DIALOG
Resource5=IDD_PROPPAGE_LARGE3
Resource6=IDD_PROPPAGE_LARGE2

[CLS:CMy802_1XConnectorApp]
Type=0
BaseClass=CWinApp
HeaderFile=802_1X Connector.h
ImplementationFile=802_1X Connector.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=802_1X ConnectorDlg.cpp
ImplementationFile=802_1X ConnectorDlg.cpp
LastObject=CAboutDlg

[CLS:CMy802_1XConnectorDlg]
Type=0
BaseClass=CDialog
HeaderFile=802_1X ConnectorDlg.h
ImplementationFile=802_1X ConnectorDlg.cpp
Filter=D
LastObject=IDC_ABOUT

[CLS:CChooseCard]
Type=0
BaseClass=CDialog
HeaderFile=ChooseCard.h
ImplementationFile=ChooseCard.cpp

[CLS:CProPage1]
Type=0
BaseClass=CPropertyPage
HeaderFile=ProPage1.h
ImplementationFile=ProPage1.cpp
Filter=D
VirtualFilter=idWC
LastObject=CProPage1

[CLS:CProPage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=ProPage2.h
ImplementationFile=ProPage2.cpp

[CLS:CProPage3]
Type=0
BaseClass=CPropertyPage
HeaderFile=ProPage3.h
ImplementationFile=ProPage3.cpp

[CLS:CProSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=ProSheet.h
ImplementationFile=ProSheet.cpp
LastObject=CProSheet

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MY802_1XCONNECTOR_DIALOG]
Type=1
Class=CMy802_1XConnectorDlg
ControlCount=16
Control1=IDC_CONNECT,button,1342275584
Control2=IDC_DISCONNECT,button,1342275584
Control3=IDC_STATIC,static,1342177806
Control4=IDC_ABOUT,button,1342275584
Control5=IDC_USERPWD,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_TIME,static,1342308352
Control8=IDC_STATIC,static,1342177280
Control9=IDC_STATIC,static,1342177280
Control10=IDC_EDIT1,edit,1342374016
Control11=IDC_EDIT2,edit,1342242976
Control12=IDC_CHECK1,button,1342242819
Control13=IDC_CONFIG,button,1342275584
Control14=IDC_LIST1,SysListView32,1350664201
Control15=IDC_VIPCHECK,button,1476460547
Control16=IDC_VMACCHECK,button,1476460547

[DLG:IDD_DIALOG1]
Type=1
Class=CChooseCard
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_CARDLIST,listbox,1351682049

[DLG:IDD_PROPPAGE_LARGE1]
Type=1
Class=CProPage1
ControlCount=17
Control1=IDC_IP,SysIPAddress32,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GATEWAY,SysIPAddress32,1342242816
Control7=IDC_NETMASK,SysIPAddress32,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_MAC1,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_MAC2,edit,1350631552
Control12=IDC_MAC3,edit,1350631552
Control13=IDC_MAC4,edit,1350631552
Control14=IDC_MAC5,edit,1350631552
Control15=IDC_MAC6,edit,1350631552
Control16=IDC_COMBO2,combobox,1344340227
Control17=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_LARGE2]
Type=1
Class=CProPage2
ControlCount=3
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO1,button,1342177289
Control3=IDC_RADIO2,button,1342177289

[DLG:IDD_PROPPAGE_LARGE3]
Type=1
Class=CProPage3
ControlCount=1
Control1=IDC_STATIC,static,1342308352

