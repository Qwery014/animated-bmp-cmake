#pragma once

#include "afxwin.h"
#include <fstream>
#include <string>
using namespace std;

class LoadFileConfig {
public:
    int width;
    int height;
    int imgWidth;
    int imgHeight;
    string url;
    int rows;
    int columns;
    int lastRow;
    int l;
    int t;
    int id;

    LoadFileConfig(
        int width,
        int height,
        int imgWidth,
        int imgHeight,
        string url,
        int rows,
        int columns,
        int lastRow,
        int l,
        int t,
        int id
    ) : width(width),
        height(height),
        imgWidth(imgWidth),
        imgHeight(imgHeight),
        url(url),
        rows(rows),
        columns(columns),
        lastRow(lastRow),
        l(l),
        t(t),
        id(id)
    {
    }
};

class CMyWindow : public CFrameWnd{

public:
	CMyWindow();

	void OnButtonClicked();

	void LoadFile(LoadFileConfig LoadFileConfigVar);

	void LoadMyBitmap(int shiftX, int shiftY, int index, unsigned char* pointerToImageData, LoadFileConfig LoadFileConfigVar);


	CButton myButton;
	CStatic imageStatic;
    CStatic imageStatic1;
    CStatic imageStatic2;

	int imgIdCounter = 0;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	HBITMAP bitmap[12];
    HBITMAP bitmap1[12];
    HBITMAP bitmap2[12];


	DECLARE_MESSAGE_MAP();
};

extern LoadFileConfig LoadFileConfigVar;
extern LoadFileConfig LoadFileConfigVar1;
extern LoadFileConfig LoadFileConfigVar2;