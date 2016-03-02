#pragma once



#include <string>


class TFileManager
{

	TFileManager();
public:
	~TFileManager();
	static TFileManager* getInst() { static TFileManager p; return &p; }
	void loadDirectry(const std::string dirPath);


	//resolution
	int m_W, m_H, m_D;

	//pitch
	double m_pW, m_pH, m_pD;

	//window size
	float m_valMax, m_valMin;

	//volume image
	float *m_vol;


	void getSliceImg_Zth_slice(int z, float *img)
	{
		memcpy(img, &m_vol[z * m_W * m_H], sizeof(float) * m_W * m_H);

	}



};

