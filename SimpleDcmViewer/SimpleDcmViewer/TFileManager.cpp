#include "stdafx.h"
#include "TFileManager.h"

#include "./ThirdParty/tdcmtk.h"


#include <vector>
#include <algorithm>
using namespace std;


TFileManager::TFileManager()
{
	m_volume = 0;
	m_W = m_H = m_D = 0;
	m_pW = m_pH = m_pD = 0;
}



TFileManager::~TFileManager()
{
	if (m_volume != 0)
	{
		for (int i = 0; i < m_D; ++i) delete[] m_volume[i];
		delete[] m_volume;
	}

}





class LessString {
public:
	bool operator()(const string& rsLeft, const string& rsRight) const {
		if (rsLeft.length() == rsRight.length()) return rsLeft < rsRight;
		else                                    return rsLeft.length() < rsRight.length();
	}
};


static void t_getAllFltFilesInDir(const char *dirpath, vector<string> &files)
{
	string ss = string(dirpath) + string("\\*.*"); 
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileA(ss.c_str(), &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "error %s\n", dirpath);
		return;
	}

	// craul all files
	do {
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			string f    = string(fd.cFileName);
			string fext = f.substr(f.length() - 4, 4);

			if ( strcmp(fext.c_str(), ".dcm") == 0 || strcmp(fext.c_str(), ".DCM") == 0) files.push_back(f);
		}
	} while (FindNextFile(hFind, &fd)); 

	FindClose(hFind);
	sort(files.begin(), files.end(), LessString());
}





void TFileManager::loadDirectry(const string dirPath)
{
	if (m_volume != 0) 
	{
		for (int i = 0; i < m_D; ++i) delete[] m_volume[i];
		delete[] m_volume;
	}


	//read all dcm in the dirPath
	vector<string> files;
	t_getAllFltFilesInDir(dirPath.c_str(), files );

	if( files.size() < 2 ) 
	{
		fprintf( stderr, "no file exist\n");
		return; 
	}

	//read initial frame to get size info
	double zPos0;
	{
		Tdcmtk tdcm((dirPath + "\\" + files[0]).c_str());
		int fNum, W,H;
		tdcm.getSize(W, H, fNum);
		m_W   = W;
		m_H   = H;
		m_D   = (int)files.size();
		m_pW  = tdcm.getPitchX();
		m_pH  = tdcm.getPitchY();
		zPos0 = tdcm.getZPos();
		m_volume = new float*[m_D];
		fprintf(stderr, "resolution %d %d %d\n", m_W, m_H, m_D);

	}

	//load all dicom file
	for (int k = 0; k < m_D; ++k)
	{
		Tdcmtk tdcm( (dirPath + "\\" + files[k] ).c_str());

		int W, H, fNum;
		tdcm.getSize(W, H, fNum);

		if (fNum > 1 || W != m_W || H != m_H )
		{
			AfxMessageBox("Format Error, one or some dicom file(s) have a different resolution");
			exit(0);
		}
		if (k == 1) m_pD = fabs(zPos0 - tdcm.getZPos());


		m_volume[k] = new float[m_W * m_H];
		tdcm.getPixelsAs<float>(m_volume[k]);

		if( k % 100 == 0 ) fprintf( stderr, "[%d/%d]done...", k, m_D);
	}

	m_valMin =  FLT_MAX;
	m_valMax = -FLT_MAX;

	for (int z = 0; z < m_D; ++z)
	{ 
		for (int i = 0; i < m_W*m_H; ++i)
		{
			m_valMin = min(m_valMin, m_volume[z][i]);
			m_valMax = max(m_valMax, m_volume[z][i]);
		}
	}

	fprintf(stderr, "%f %f\n", m_valMin, m_valMax);

}