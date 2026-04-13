#include "header.h"
#include "AutoMoving.h"
#include "UtilCollisionDetection.h"


void AutoMoving::virtDraw() {
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		color);
}
	
//void AutoMoving::virtDoUpdate(int iCurrentTime) {
//	if (CollisionDetection::checkCircles(
//			dynamic_cast<SCYSY3Engine*>(getEngine())->getFollowMouse()->getXCentre(),
//			dynamic_cast<SCYSY3Engine*>(getEngine())->getFollowMouse()->getYCentre(), 
//			getXCentre(),
//			getYCentre(),
//			dynamic_cast<SCYSY3Engine*>(getEngine())->getFollowMouse()->getDrawWidth()/2 + getDrawWidth()/2
//			)
//		)
//	{
//		color = 0xFF0000;
//	}
//	else {
//		color = 0x000000;
//	}
//
//	if (direction) {
//		m_iCurrentScreenX += speed;
//	}
//	else {
//		m_iCurrentScreenX -= speed;
//	}
//
//	if (m_iCurrentScreenX >= 800) {
//		direction = false;
//	}
//	else if (m_iCurrentScreenX <= 200) {
//		direction = true;
//	}
//}