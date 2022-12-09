#pragma once
#include <afxcmn.h>
class CEditableListCtrl : public CListCtrl
{
public:

	int GetRowFromPoint( CPoint &point, int *col ) const;
	CEdit* EditSubLabel( int nItem, int nCol );

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSetLabelText(int row,int col,CString str);
protected:

	DECLARE_MESSAGE_MAP()
};