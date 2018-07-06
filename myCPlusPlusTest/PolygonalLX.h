/*!
* \file 	PolygonalLX.h
* \brief	
*
*	多边形点位置判断接口
*
* \version  1.0.0
* \date		2018/05/07
*/
#ifndef _H_POLYGONALLX_H_
#define _H_POLYGONALLX_H_
#include <limits>
#include <vector>
using std::vector;
using std::numeric_limits;


/// \brief 坐标值结构体
struct LXPoint
{
	LXPoint()
	   : m_dX(0.0f)
	   , m_dY(0.0f)
	   /*, m_dZ(0.0f)*/ 
	{

	}
	LXPoint( double dX
		   , double dY
	       /*, double dZ */)
		: m_dX(dX)
		, m_dY(dY)
		/*, m_dZ(dZ)*/
	{

	}

	double m_dX;  // x
	double m_dY;  // y
	/*double m_dZ;  // z*/
};



/// \brief 点所在位置类型
enum LXPtPosType 
{
   E_POS_TOP = 0,  // 上
   E_POS_BOTTOM,   // 下
   E_POS_LEFT,     // 左
   E_POS_RIGHT,     // 右
   E_POS_INTERNAL   // 内部
};


/// \brief 二维矩形
class CLXRect
{
public:
	CLXRect()
	{
		double dMax = numeric_limits<double>::max();
		double dMin = numeric_limits<double>::min();

		m_leftT.m_dX = dMax;
		m_leftT.m_dY = dMin;

		m_leftB.m_dX = dMax;
		m_leftB.m_dY = dMax;

		m_rightT.m_dX = dMin;
		m_rightT.m_dY = dMin;

		m_rightB.m_dX = dMin;
		m_rightB.m_dY = dMax;

	}


	/// \brief 加入点扩张矩形
	/// \param pt  [in]
	void Update(const LXPoint& pt)
	{
		//[1] 获取点方位
		LXPtPosType ePtPosType = PtPosType(pt);

		// 根据点点方位更新矩形
		switch ( ePtPosType )
		{
			case E_POS_TOP:  //<1> 上面
			{
				// 若在凸字形内
				if (pt.m_dX > m_leftT.m_dX
					&& pt.m_dX < m_rightT.m_dX)
				{

				}
				else if( pt.m_dX<=m_leftT.m_dX  )
				{
					m_leftT = pt;
				}
				else/* if( pt.m_dX>= m_rightT.m_dX  )*/
				{
					m_rightT = pt;
				}
			
			}
			break;
		case E_POS_BOTTOM: //<2> 下面 
			{
			    // 若在凸字形内
				if (pt.m_dX > m_leftB.m_dX
					&& pt.m_dX < m_rightB.m_dX)
				{

				}
				else if (pt.m_dX <= m_leftB.m_dX)
				{
					m_leftB = pt;
				}
				else /*if (pt.m_dX >= m_rightB.m_dX)*/
				{
					m_rightB = pt;
				}

			}
			break;
		case E_POS_LEFT:   //<3> 左边 
			{
			    // 若在凸字形内
			   if ( pt.m_dY< m_leftT.m_dY
				   && pt.m_dY> m_leftB.m_dY  )
			   {

			   }
			   else if( pt.m_dY>=m_leftT.m_dY )
			   {
				   m_leftT = pt;
			   }
			   else 
			   {
				   m_leftB = pt;
			   }

			}
			break;
		case E_POS_RIGHT:  //<4> 右边
			{
				// 若在凸字形内
				if ( pt.m_dY<m_rightT.m_dY
					&& pt.m_dY>m_rightB.m_dY )
				{

				}
				else if( pt.m_dY>= m_rightT.m_dY )
				{
					m_rightT = pt;
				}
				else
				{
					m_rightB = pt;
				}

			}
			break;
		default:
			break;
		}
	}
	
	
	/// \brief 判断点在矩形上下左右方位 
	/// \param blackPt [in] 黑色点坐标
	/// \return 黑色点坐标做出方位
	LXPtPosType PtPosType(const LXPoint& blackPt)  const
	{
		

		//[1] 在上面?
		if ( blackPt.m_dY>m_leftT.m_dY
			&& blackPt.m_dY>m_rightT.m_dY)
		{
			return E_POS_TOP;
		}
		else if ( blackPt.m_dY<m_leftB.m_dY
			    && blackPt.m_dY<m_rightB.m_dY ) //[2] 在下面?
		{
			return E_POS_BOTTOM;
		}
		else if( blackPt.m_dX< m_leftT.m_dX
			    && blackPt.m_dX< m_leftB.m_dX )  //[3] 在左边?
		{
			return E_POS_LEFT;
		}
		else if( blackPt.m_dX>m_rightT.m_dX
			    && blackPt.m_dX>m_rightB.m_dX )   //[4] 在右边?
		{
			return E_POS_RIGHT;
		}

		return E_POS_INTERNAL;

	}
   


private:
	LXPoint m_leftT; // 左上
	LXPoint m_rightT; // 右上
	LXPoint m_leftB; // 左下
	LXPoint m_rightB; // 右下
};


//(仿)
class CPolygonalLX
{
public:
	CPolygonalLX(const vector<LXPoint>& vRedPts);

	
	/// \brief 判断点在矩形上下左右方位 
	/// \param blackPt [in] 黑色点坐标
	/// \return 黑色点坐标做出方位
	LXPtPosType operator()(const LXPoint& blackPt)  const;

private:

	/// \brief 根据红色基准点拟合规格矩形
	/// \param vRedPts  [in]     红色基准点
	/// \param clRect   [in/out] 扩展出来的矩形
	void FitRectangle(const vector<LXPoint>& vRedPts
	                  ,  CLXRect& clRect );



	CLXRect m_clRect;                   // 扩展判断矩形 


};


#endif // _H_POLYGONALLX_H_ 

