#include "stdafx.h"

#include "tdcmtk.h"



//ref: http://wiki.nakaguchi.org/index.php?DCMTK

extern void t_info  (const char* fmt, ...);
extern void t_debug (const char* fmt, ...);



bool t_getTagValInt(DcmDataset *DataSet, DcmTagKey tagKey, int &value)
{
    DcmElement *elem = NULL;
    DcmTag tag(tagKey);

    if ( DataSet->findAndGetElement(tag, elem).bad() || elem->getLength() == 0) return false;

    Sint16 rvS16;
    Sint32 rvS32;
    Uint8  rvU8 ;
    Uint16 rvU16;
    Uint32 rvU32;
    if      ( elem->getSint16( rvS16 ).good() ) { value = (int)rvS16; }
    else if ( elem->getSint32( rvS32 ).good() ) { value = (int)rvS32; }
    else if ( elem->getUint8 ( rvU8  ).good() ) { value = (int)rvU8 ; }
    else if ( elem->getUint16( rvU16 ).good() ) { value = (int)rvU16; }
    else if ( elem->getUint32( rvU32 ).good() ) { value = (int)rvU32; }
    else {
        t_info("%s is not integer value", tag.getTagName());
        return false;
    }
    return true;
}




void t_getPitchInfo( DcmFileFormat *ff, double pitch[2], double posInfo[3])
{
    if( ff->getDataset()->findAndGetFloat64( DCM_PixelSpacing        , pitch  [0], 0 ).bad() ) pitch[0] = -1;
    if( ff->getDataset()->findAndGetFloat64( DCM_PixelSpacing        , pitch  [1], 1 ).bad() ) pitch[1] = -1;
    if( ff->getDataset()->findAndGetFloat64( DCM_ImagePositionPatient, posInfo[0], 0 ).bad() ) posInfo[0] = -1;
    if( ff->getDataset()->findAndGetFloat64( DCM_ImagePositionPatient, posInfo[1], 1 ).bad() ) posInfo[1] = -1;
    if( ff->getDataset()->findAndGetFloat64( DCM_ImagePositionPatient, posInfo[2], 2 ).bad() ) posInfo[2] = -1;

    //the following code provide thickness (slice thick ness for integration (!= pitch))
    //if( ff->getDataset()->findAndGetFloat64( DCM_SliceThickness, pz    ).bad() ) pz = -1;
}









Tdcmtk::Tdcmtk( const char *fname )
{    
    m_FileFormat = new DcmFileFormat;
    OFCondition status = m_FileFormat->loadFile(fname);

    if ( status.bad() )
    {
        t_info( "cannot open the file!!!");
        if ( m_FileFormat )
        {
            delete m_FileFormat;
            m_FileFormat = 0;
        }
        return;
    }

    m_dataSet = m_FileFormat->getDataset();

    m_W = m_H = m_fNum = 0;
    m_nBits = m_bSined = m_bChNum  = m_bChArrange = 0;

    //size
    t_getTagValInt(m_dataSet, DCM_Columns            , m_W    );
    t_getTagValInt(m_dataSet, DCM_Rows               , m_H    );
    t_getTagValInt(m_dataSet, DCM_NumberOfFrames     , m_fNum );

    //pixel configureation
    int bs, ba, hb, spp, plc, pr;
    t_getTagValInt(m_dataSet, DCM_BitsStored         , bs     ); // bits for 1 pixel (actually used)
    t_getTagValInt(m_dataSet, DCM_BitsAllocated      , ba     ); // bits for 1 pixel (allocated)
    t_getTagValInt(m_dataSet, DCM_HighBit            , hb     );
    t_getTagValInt(m_dataSet, DCM_SamplesPerPixel    , spp    ); // 1:gray, 3:rgb
    t_getTagValInt(m_dataSet, DCM_PlanarConfiguration, plc    );
    t_getTagValInt(m_dataSet, DCM_PixelRepresentation, pr     ); //unsigned (0) or signed (1)
    m_nBits      = ba ;
    m_bSined     = pr ;
    m_bChNum     = spp;
    m_bChArrange = plc;



    t_getPitchInfo( m_FileFormat, m_pitch, m_pos );
}

void Tdcmtk::getSize  ( int &W, int &H, int &fNum )
{
    W    = m_W   ;
    H    = m_H   ;
    fNum = m_fNum;
}

void Tdcmtk::getFormat( int &chNum, int &bitNum, int &bSigned  )
{
    chNum   = m_bChNum;
    bitNum  = m_nBits ;
    bSigned = m_bSined;
}



//他のformatは必要に応じて作る
bool Tdcmtk::getPixels_SInt16(const Sint16* &data)
{
    if ( !m_dataSet )
    {
        t_info("fails to open the file" );
        return false;
    }

    if( m_nBits != 16 || !m_bSined ){
        t_info("wrong format\n");
        return false;
    }

    // Load pixel data into memory
    unsigned long psize = 0;

    if ( m_dataSet->findAndGetUint16Array( DCM_PixelData, (const Uint16*&) data, &psize,false ).bad() ) return false;
    //if ( m_dataSet->findAndGetSint16Array( DCM_PixelData, data, &psize,false ).bad() ) return false;

    return true;
}


bool Tdcmtk::getPixels_UInt16(const Uint16* &data)
{
	if (!m_dataSet)
	{
		t_info("fails to open the file");
		return false;
	}
	if (m_nBits != 16 || m_bSined) {
		t_info("wrong format\n");
		return false;
	}

	// Load pixel data into memory
	unsigned long psize = 0;

	if (m_dataSet->findAndGetUint16Array(DCM_PixelData, (const Uint16*&)data, &psize, false).bad()) return false;
	//if ( m_dataSet->findAndGetSint16Array( DCM_PixelData, data, &psize,false ).bad() ) return false;

	return true;
}



//data should be allocated
bool Tdcmtk::getPixelsToFlt(float* data)
{
	if (!m_dataSet)
	{
		t_info("fails to open the file");
		return false;
	}

	if (m_nBits == 16 && m_bSined) 
	{
		const Sint16 *v = 0;
		getPixels_SInt16(v);
		for (int i = 0, s = m_W * m_H; i < s; ++i) data[i] = v[i];
		delete[] v;
	}
	else if (m_nBits == 16 && !m_bSined)
	{
		const Uint16 *v = 0;
		getPixels_UInt16(v);
		for (int i = 0, s = m_W * m_H; i < s; ++i) data[i] = v[i];
		delete[] v;
	}
	else
	{
		t_info("this file type is not implemeted yet\n");
		return false;
	}

	return true;
}




