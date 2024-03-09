#include <iostream>

#include "base/xd.h"
#include "xd_os.h"

namespace nXD {

class Application: public nXD::OS::KeyListener, public nXD::OS::PointerListener
{
	OS::WDGT_T m_widget;
	OS m_os;
	bln m_is_playing;
public:
	Application() : m_widget(nullptr), m_is_playing(false) {}
	x_result fInitX();
	x_result fRunX();

public:
	OS::HandleResult onKey(const OS::INPUT_KEY &) override;
	OS::HandleResult onPointer(si4, const I4 &) override;

	virtual ~Application() {}
};

OS::HandleResult Application::onKey(const OS::INPUT_KEY &_key)
{
	if(_key.key == nXD::XDE_KEY_ESC){
		m_is_playing = false;
	}
	else {
		mLOG(_key.key);
	}
	return OS::HandleResult_Error;
}

OS::HandleResult Application::onPointer(si4, const I4 &)
{
	return OS::HandleResult_Error;
}

x_result Application::fInitX()
{
	return nXD::CRITICAL_SUCCESS;
}

x_result Application::fRunX()
{
	m_widget = nXD::OS::iWdgtCreateP();
	m_os.fKeyListenerSetA(this).fPointerListenerSetA(this);

	nXD::I2 screen_size;
	OS::iScreenSizeGetX(screen_size);

	nXD::I4 widget_border(
				mVAR("left", screen_size.x/4),
				mVAR("right", screen_size.y/4),
				mVAR("top", screen_size.x/2),
				mVAR("bottom", screen_size.y/2)
	);
	nXD::OS::iWdgtInitX("Application", widget_border, m_widget);
	nXD::OS::iWdgtShowX(true, m_widget);

	m_is_playing = true;

	while(m_is_playing){
		m_os.fSyncX();
	}

	OS::iWdgtDestroyX(m_widget);
	return nXD::CRITICAL_SUCCESS;
}

}// namespace nXD

int main()
{
	nXD::Application app;
	mXD_CHECK(app.fInitX());
	mXD_CHECK(app.fRunX());
	return 0;
}
