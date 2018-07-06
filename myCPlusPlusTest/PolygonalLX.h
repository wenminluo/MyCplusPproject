/*!
* \file 	PolygonalLX.h
* \brief	
*
*	����ε�λ���жϽӿ�
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


/// \brief ����ֵ�ṹ��
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



/// \brief ������λ������
enum LXPtPosType 
{
   E_POS_TOP = 0,  // ��
   E_POS_BOTTOM,   // ��
   E_POS_LEFT,     // ��
   E_POS_RIGHT,     // ��
   E_POS_INTERNAL   // �ڲ�
};


/// \brief ��ά����
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


	/// \brief ��������ž���
	/// \param pt  [in]
	void Update(const LXPoint& pt)
	{
		//[1] ��ȡ�㷽λ
		LXPtPosType ePtPosType = PtPosType(pt);

		// ���ݵ�㷽λ���¾���
		switch ( ePtPosType )
		{
			case E_POS_TOP:  //<1> ����
			{
				// ����͹������
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
		case E_POS_BOTTOM: //<2> ���� 
			{
			    // ����͹������
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
		case E_POS_LEFT:   //<3> ��� 
			{
			    // ����͹������
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
		case E_POS_RIGHT:  //<4> �ұ�
			{
				// ����͹������
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
	
	
	/// \brief �жϵ��ھ����������ҷ�λ 
	/// \param blackPt [in] ��ɫ������
	/// \return ��ɫ������������λ
	LXPtPosType PtPosType(const LXPoint& blackPt)  const
	{
		

		//[1] ������?
		if ( blackPt.m_dY>m_leftT.m_dY
			&& blackPt.m_dY>m_rightT.m_dY)
		{
			return E_POS_TOP;
		}
		else if ( blackPt.m_dY<m_leftB.m_dY
			    && blackPt.m_dY<m_rightB.m_dY ) //[2] ������?
		{
			return E_POS_BOTTOM;
		}
		else if( blackPt.m_dX< m_leftT.m_dX
			    && blackPt.m_dX< m_leftB.m_dX )  //[3] �����?
		{
			return E_POS_LEFT;
		}
		else if( blackPt.m_dX>m_rightT.m_dX
			    && blackPt.m_dX>m_rightB.m_dX )   //[4] ���ұ�?
		{
			return E_POS_RIGHT;
		}

		return E_POS_INTERNAL;

	}
   


private:
	LXPoint m_leftT; // ����
	LXPoint m_rightT; // ����
	LXPoint m_leftB; // ����
	LXPoint m_rightB; // ����
};


//(��)
class CPolygonalLX
{
public:
	CPolygonalLX(const vector<LXPoint>& vRedPts);

	
	/// \brief �жϵ��ھ����������ҷ�λ 
	/// \param blackPt [in] ��ɫ������
	/// \return ��ɫ������������λ
	LXPtPosType operator()(const LXPoint& blackPt)  const;

private:

	/// \brief ���ݺ�ɫ��׼����Ϲ�����
	/// \param vRedPts  [in]     ��ɫ��׼��
	/// \param clRect   [in/out] ��չ�����ľ���
	void FitRectangle(const vector<LXPoint>& vRedPts
	                  ,  CLXRect& clRect );



	CLXRect m_clRect;                   // ��չ�жϾ��� 


};


#endif // _H_POLYGONALLX_H_ 

