#ifndef TDCMTK_H
#define TDCMTK_H



// DCMTK
#include "./dcmtk/dcmdata/dctk.h"

#pragma comment(lib, "dcmdata.lib")
#pragma comment(lib, "oflog.lib")
#pragma comment(lib, "ofstd.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "ws2_32.lib"  )
#pragma comment(lib, "wsock32.lib" )
class Tdcmtk
{
    DcmFileFormat* m_FileFormat;
    DcmDataset*	   m_dataSet;

    int m_W     ;
    int m_H     ;
    int m_fNum  ;
    int m_nBits ;
    int m_bSined;
    int m_bChNum    ;//1:gray 3 rgb
    int m_bChArrange;//0:normal (rgba rgba), > 1 (rrrr... gggg... bbb...)

    double m_pitch[2]; //pixel pitch (x,y)
    double m_pos[3]  ; //slice pos (x,y,z)

public:
    Tdcmtk( const char *fname );
    bool isOpened(){ return m_dataSet != 0; }

    void getSize  ( int &W, int &H, int &fNum );


    // if failed return -1
    double getPitchX ( ){ return m_pitch[0]; }
    double getPitchY ( ){ return m_pitch[1]; }
    double getZPos   ( ){ return m_pos  [2]; }

    void getFormat( int &chNum, int &bitNum, int &bSigned );
    bool getPixels_SInt16( const Sint16* &data );

    //bool getTagValue( DcmTagKey tagKey, int &value );

private:
    //DcmElement* getTagElem(DcmTagKey tagKey);

};

#endif // TDCMTK_H
