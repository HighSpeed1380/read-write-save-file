
// MFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDlg dialog



CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_EditableList);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMFCDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &CMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCDlg message handlers

BOOL CMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	DWORD dwStyle = m_EditableList.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	m_EditableList.SetExtendedStyle(dwStyle);

	LVCOLUMN lvColumn;
	int nCol;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 230;
	lvColumn.pszText = L"Propery";
	nCol = m_EditableList.InsertColumn(0, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 230;
	lvColumn.pszText = L"Value";
	m_EditableList.InsertColumn(1, &lvColumn);

	m_EditableList.SetExtendedStyle(m_EditableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EDITLABELS);

	// Insert a few example list items

	// TODO: Add extra initialization here
	UINT    nActual = 0;
	CFile   myFile;
	FileName = L"C://Program Files//Kingsoft//Liquid//local_settings.dat";

	CString strLine;
	int maxCount = 10000;

	CStdioFile file(FileName, CFile::modeRead);
	while (file.ReadString(strLine)) {
		arrLines.Add(strLine); 
		const int iToken = strLine.Find(';');
		if (iToken >= 0)
		{
			CString String = strLine.Left(iToken);

			const int iEquator = String.Find('=');
			if (iEquator >= 0)
			{
				CString propertyString = String.Left(iEquator);
				CString valueString = String.Mid(iEquator + 1);

				int l_iItem = m_EditableList.InsertItem(LVIF_TEXT | LVIF_STATE, maxCount, propertyString, 0, LVIS_SELECTED, 0, 0);
				m_EditableList.SetItemText(l_iItem, 1, valueString);
			}
		}
	}
	file.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
}


void CMFCDlg::OnBnClickedButton1()
{

	// TODO: Add your control notification handler code here
	UINT n = arrLines.GetCount();
	int l_iItem = m_EditableList.InsertItem(LVIF_TEXT | LVIF_STATE, n, NULL, 0, LVIS_SELECTED, 0, 0);
	m_EditableList.SetItemText(l_iItem, 1, NULL);
}


void CMFCDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	
}


void CMFCDlg::OnBnClickedOk()
{
	CString str("");
	UINT n = m_EditableList.GetItemCount();
	for (int i = 0; i < n;i++) {
		CString property = m_EditableList.GetItemText(i, 0);
		CString value = m_EditableList.GetItemText(i, 1);
		str += CString(property + L'=' + value + L";\n");
	}

	CStdioFile file;
	if (!file.Open(FileName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive))
		return;
	file.SeekToEnd();
	file.WriteString(str); // \r\n to move the cursor to the next line
	file.Close();
	// TODO: Add your control notification handler code here
	/*CDialogEx::OnOK();*/
}
