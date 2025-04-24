// Final Project Simulation of JUKEBOX
//Made by: Nathan Gumataotao using MFC VS


#include "pch.h"
#include "JukeBox.h"
#include "framework.h"
#include "Final.h"
#include "FinalDlg.h"
#include "afxdialogex.h"
#include "vfw.h"
#include <stdlib.h>

#include <sstream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#define IDC_MYTIMER 1001 //Defines Timer ID
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CFinalDlg dialog



CFinalDlg::CFinalDlg(CWnd* pParent /*=nullptr*/)//Cant get rid of this warning
	: CDialogEx(IDD_FINAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	

}

void CFinalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFinalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFinalDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CFinalDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFinalDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT4, &CFinalDlg::OnEdit1Changed)//Really nice feature that fires function on an edit box being updated 
	ON_EN_CHANGE(IDC_EDIT3, &CFinalDlg::OnEdit2Changed)//same with this 
	ON_WM_TIMER()//defines timer
END_MESSAGE_MAP()


// CFinalDlg message handlers

BOOL CFinalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	CComboBox* pCombo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO1)); // Defining Songs in Combo Box
	pCombo->InsertString(0, _T("Purple Rain, Prince"));
	pCombo->InsertString(1, _T("Hot Stuff, Donna Summer"));
	pCombo->InsertString(2, _T("Total Eclipse of the Heart, Bonnie Tyler"));
	pCombo->InsertString(3, _T("Ace of Spades, Motorhead"));
	pCombo->InsertString(4, _T("Pour Some Sugar on Me, Def Leppard"));
	pCombo->InsertString(5, _T("Burning Down the House, Talking Heads"));
	pCombo->InsertString(6, _T("Hip to Be Sqauare, Huey Lewis and the News"));
	pCombo->InsertString(7, _T("November Rain, Gun's and Roses"));
	pCombo->SetCurSel(0);

	CString play;
	CString menu;

	CEdit* playEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BUTTON1));
	CEdit* menuEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COMBO1));

	playEdit->EnableWindow(false);// Disables the Jukebox before a coin is inserted so you cant just play songs
	menuEdit->EnableWindow(false);


	CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC2));
	pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
	HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	pPicture->SetBitmap(hb);
	
	//This allows for the bitmap files to be loaded into an array and can all be called seperatley instead of
	//having to call this function for every song
	m_BitmapHandles[0] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP16)); //Purple Rain
	m_BitmapHandles[1] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP11)); //Bad Girls
	m_BitmapHandles[2] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP12)); //Faster Than the Speed of Light
	m_BitmapHandles[3] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP10)); //Ace of Spades
	m_BitmapHandles[4] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP15)); //Hysteria
	m_BitmapHandles[5] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP17)); //Speaking in Tongues
	m_BitmapHandles[6] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP13)); //FORE!
	m_BitmapHandles[7] = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP14)); //Use Your Illusion

		return TRUE;  
	
}

void CFinalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFinalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CFinalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//Checks to see if IDC_EDIT1 has the string "Thank You" and will enable the Combo box and the Button to play Music
void CFinalDlg::OnEdit1Changed() {

	CString str;
	CString check = _T("Thank You\n");
	CString check2 = (_T("Invalid"));

	GetDlgItemText(IDC_EDIT4, str);

	BOOL bEnableButtons = (str == check);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(bEnableButtons);
	GetDlgItem(IDC_COMBO1)->EnableWindow(bEnableButtons);
	
	if (!bEnableButtons) {
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	}
	
	
}


//This checks to see of the edit box displaying what song is playing is changed and will automatically disable 
//the combo and button for playing music, as I wouldn't want someone to be able to play another song without first 
//insterting another coin
void CFinalDlg::OnEdit2Changed() {
	
	

	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	
	if (!str.IsEmpty()) {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		GetDlgItem(IDC_COMBO1)->EnableWindow(false);

	}


}


//Timer function that when called starts a timer for the alloted time and when it ends, indicates
// that a song has ended along with allowing for another coin to be inserted into the Edit box for 
// another song to be played.
void CFinalDlg::OnTimer(UINT_PTR nIDEvent) {

	if (nIDEvent == IDC_MYTIMER) {

		GetDlgItem(IDC_EDIT1)->EnableWindow(true);
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("Song Ended"));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		KillTimer(IDC_MYTIMER);
	}

}

void CFinalDlg::OnCbnSelchangeCombo1(){}


//Plays and calls the song class for which ever combo box option was selected 
// also starts a timer, and changes the Image for the picture controller
// I have capped the timer at 5 seconds as I thought it was a little unnecesarry for 
// this simulation to have every song play its actual length as some of them are almost 
// 9 minutes long.
void CFinalDlg::OnBnClickedButton1()
{
	CEdit* output = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* current = (CEdit*)GetDlgItem(IDC_EDIT3);
	
	//disables the edit box to put in a coin so a song must complete
	//  
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int n = pCombo->GetCurSel();
	ostringstream sout;

	//Gets picture controller

	CStatic* albumCover = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC2));
	
	if (n == 0) {
		songs::prince aPrince;
		aPrince.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Purple Rain"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[0]);
	}
	else if (n == 1) {
		songs::summer aSummer;
		aSummer.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Hot Stuff"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[1]);
	}
	else if (n == 2) {
		songs::tyler aTyler;
		aTyler.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Total Eclipse of the Heart"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[2]);
	}
	else if (n == 3) {
		songs::motor aMotor;
		aMotor.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Ace of Spades"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[3]);
	}
	else if (n == 4) {
		songs::lepard aLeppard;
		aLeppard.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Pour Some Sugar on Me"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[4]);
	}
	else if (n == 5) {
		songs::Heads aHeads;
		aHeads.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Burning Down the House"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[5]);
	}
	else if (n == 6) {
		songs::Huey aHuey;
		aHuey.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("Hip to be Square"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[6]);
	}
	else if (n == 7) {
		songs::guns aGuns;
		aGuns.output(sout);
		output->SetWindowText(CString(sout.str().c_str()));
		current->SetWindowText(_T("November Rain"));
		SetTimer(IDC_MYTIMER, 5000, nullptr);
		albumCover->SetBitmap(m_BitmapHandles[7]);
	}

	//the 'SetTimer' is in very song call because if this were to actually play music
	//all of the timer amounts would have to be different values so this addition is
	//really only for future development.

}


//Hides and unhides the information tab
void CFinalDlg::OnBnClickedCheck1()
{
	CString mEdit1;
	CEdit* pEdit1 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT2));

	CButton* pCheckBox = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK1));


	if (pCheckBox->GetCheck() == BST_CHECKED)
	{
		pEdit1->ShowWindow(SW_HIDE);
	}
	else
	{
		pEdit1->ShowWindow(SW_SHOW);
	}
}


//takes in a coin "value" and outputs either "Thank You" or "Invalid"
//this is used for tracking whether the combo and Edit box for playing
//songs should be enabled or disabled 
void CFinalDlg::OnBnClickedButton2()
{
	CString mEdit1;
	CString  mEdit4;
	CEdit* pEdit1 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT1));
	CEdit* pEdit4 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT4));
	pEdit1->GetWindowText(mEdit1);


	vector<string> tokens;
	ostringstream sout;

	string i1 = CStringA(mEdit1);
	tokens.push_back(i1);
	string i2 = CStringA(mEdit1);
	tokens.push_back(i2);
	coin::coin acoin(tokens);
	acoin.output(sout);
	pEdit4->SetWindowText(CString(sout.str().c_str()));

}
