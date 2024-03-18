#include "CMyWindow.h"

int imgIdCounter = 5;


LoadFileConfig LoadFileConfigVar(84, 84, 512, 256, "chip2.bmp", 2, 6, 6, 200, 20, 5);
LoadFileConfig LoadFileConfigVar1(88, 84, 512, 256, "chip3.bmp", 3, 5, 2, 10, 20, 6);
LoadFileConfig LoadFileConfigVar2(84, 85, 512, 256, "chip4.bmp", 3, 5, 2, 100, 20, 7);


CMyWindow::CMyWindow()
{
	RECT myRect;
	myRect.left = 0;
	myRect.right = 800;
	myRect.top = 0;
	myRect.bottom = 600;

	Create(NULL, "hhhhhh", WS_OVERLAPPEDWINDOW, myRect, nullptr, nullptr, WS_EX_WINDOWEDGE, nullptr);


	RECT staticRect;
	staticRect.left = LoadFileConfigVar.l;
	staticRect.right = LoadFileConfigVar.l + LoadFileConfigVar.width;
	staticRect.top = LoadFileConfigVar.t;
	staticRect.bottom = LoadFileConfigVar.t + LoadFileConfigVar.height;
	imageStatic.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect, this, LoadFileConfigVar.id);


	RECT staticRect1;
	staticRect1.left = LoadFileConfigVar1.l;
	staticRect1.right = LoadFileConfigVar1.l + LoadFileConfigVar1.width;
	staticRect1.top = LoadFileConfigVar1.t;
	staticRect1.bottom = LoadFileConfigVar1.t + LoadFileConfigVar1.height;
	imageStatic1.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect1, this, LoadFileConfigVar1.id);

	RECT staticRect2;
	staticRect2.left = LoadFileConfigVar2.l;
	staticRect2.right = LoadFileConfigVar2.l + LoadFileConfigVar2.width;
	staticRect2.top = LoadFileConfigVar2.t;
	staticRect2.bottom = LoadFileConfigVar2.t + LoadFileConfigVar2.height;
	imageStatic2.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect2, this, LoadFileConfigVar2.id);

	LoadFile(LoadFileConfigVar);
	LoadFile(LoadFileConfigVar1);
	LoadFile(LoadFileConfigVar2);


}

void CMyWindow::OnButtonClicked()
{
}

void CMyWindow::LoadFile(LoadFileConfig LoadFileConfigVar)
{
	std::ifstream f;

	f.open(LoadFileConfigVar.url, std::ios::binary);

	f.seekg(0, std::ios::end);
	int fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	unsigned char* bytes = new unsigned char[fileSize];

	f.read((char*)bytes, fileSize);

	unsigned int width = bytes[18];

	width = width + bytes[19] * 0x100;
	width = width + bytes[20] * 0x10000;
	width = width + bytes[21] * 0x1000000;

	unsigned int height = bytes[22];

	height = height + bytes[23] * 0x100;
	height = height + bytes[24] * 0x10000;
	height = height + bytes[25] * 0x1000000;

	unsigned char* pointerToImageData = bytes + 54;

	int k = 0;

	for (int i = 0; i < LoadFileConfigVar.rows; i++)
	{
		for (int j = 0; j < LoadFileConfigVar.columns; j++)
		{
			if (k < LoadFileConfigVar.rows * LoadFileConfigVar.columns - (LoadFileConfigVar.columns - LoadFileConfigVar.lastRow))
			{
				LoadMyBitmap(j, i, k++, pointerToImageData, LoadFileConfigVar);
			}
		}
	}

	if (LoadFileConfigVar.id == 5)
	{
		imageStatic.SetBitmap(bitmap[LoadFileConfigVar.id]);
	}
	else if (LoadFileConfigVar.id == 6)
	{
		imageStatic1.SetBitmap(bitmap1[LoadFileConfigVar.id]);
	}
	else if (LoadFileConfigVar.id == 7)
	{
		imageStatic2.SetBitmap(bitmap2[LoadFileConfigVar.id]);
	}

	f.close();

	// delete[] chipImage1;

	delete[] bytes;
}


void CMyWindow::LoadMyBitmap(int shiftX, int shiftY, int index, unsigned char* pointerToImageData, LoadFileConfig LoadFileConfigVar)
{
	BITMAPINFO info;

	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = LoadFileConfigVar.width;
	info.bmiHeader.biHeight = LoadFileConfigVar.height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biCompression = 0;
	info.bmiHeader.biSizeImage = 0;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;
	info.bmiColors[0].rgbBlue = 0;
	info.bmiColors[0].rgbGreen = 0;
	info.bmiColors[0].rgbRed = 0;
	info.bmiColors[0].rgbReserved = 0;

	//DrawContext = DC
	HDC hdc = this->GetDC()->m_hDC;

	unsigned char* chipImage1 = new unsigned char[LoadFileConfigVar.width * LoadFileConfigVar.height * 3];

	for (int x = 0; x < LoadFileConfigVar.width; x++)
	{
		for (int y = 0; y < LoadFileConfigVar.height; y++)
		{
			int positionInPixel = y * LoadFileConfigVar.width + x;

			int positionInOriginalImage = x + shiftX * LoadFileConfigVar.width + (y + (LoadFileConfigVar.imgHeight - LoadFileConfigVar.height) - shiftY * LoadFileConfigVar.height) * LoadFileConfigVar.imgWidth;

			chipImage1[positionInPixel * 3 + 0] = pointerToImageData[positionInOriginalImage * 3 + 0];
			chipImage1[positionInPixel * 3 + 1] = pointerToImageData[positionInOriginalImage * 3 + 1];
			chipImage1[positionInPixel * 3 + 2] = pointerToImageData[positionInOriginalImage * 3 + 2];

		}
	}

	if (LoadFileConfigVar.id == 5)
	{
		bitmap[index] = CreateDIBitmap(hdc, &info.bmiHeader, CBM_INIT, chipImage1, &info, 0);
	}
	else if (LoadFileConfigVar.id == 6)
	{
		bitmap1[index] = CreateDIBitmap(hdc, &info.bmiHeader, CBM_INIT, chipImage1, &info, 0);
	}
	else if (LoadFileConfigVar.id == 7)
	{
		bitmap2[index] = CreateDIBitmap(hdc, &info.bmiHeader, CBM_INIT, chipImage1, &info, 0);
	}


	delete[] chipImage1;
}


BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	// ON_WM_LBUTTONDOWN() // Добавление сообщения о нажатии левой кнопки мыши в обработчик сообщений
END_MESSAGE_MAP()
