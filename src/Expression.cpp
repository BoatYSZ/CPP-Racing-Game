#include "header.h"
#include "Expression.h"


Expression::Expression(BaseEngine* pEngine, State* state_belong, SCYSY3DisplayableObject* obj_belong):
	SCYSY3DisplayableObject(pEngine, state_belong, 88, 88, true)
{
	
	relative_object = obj_belong;
	m_iCurrentScreenX = relative_object->getXCentre() + 100;
	m_iCurrentScreenY = relative_object->getYCentre() - 150;
	m_image = new SCYSY3Image("smile.png");
}

Expression::~Expression() {
}

void Expression::virtDoUpdate(int iCurrentTime) {
	m_iCurrentScreenX = relative_object->getXCentre() + 100;
	m_iCurrentScreenY = relative_object->getYCentre() - 150;

	timeRemaining -= p_BelongState->time_Increment;
	if (timeRemaining < 0) {
		getEngine()->removeDisplayableObject(this);
		getEngine()->notifyAllObjects(1, 0, 0);
		delete this;
	}
}



void Expression::virtDraw() {
	m_image->renderImageWithMask(p_BelongState->pState_ForeSurface, 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_image->getWidth(), m_image->getHeight(), -1);
}