#include "PolygonalLX.h"


CPolygonalLX::CPolygonalLX(const vector<LXPoint>& vRedPts)
{
	FitRectangle(vRedPts, m_clRect);
}


LXPtPosType CPolygonalLX::operator()(const LXPoint& blackPt)  const
{
	return m_clRect.PtPosType(blackPt);
}



void CPolygonalLX::FitRectangle(const vector<LXPoint>& vRedPts
	                           , CLXRect& clRect)
{
	//[1] 拟合出扩张矩形
	for ( auto cItPos = vRedPts.cbegin()
		 ; vRedPts.cend()!= cItPos
		 ; ++cItPos )
	{
		clRect.Update(*cItPos);
	}
	 

}