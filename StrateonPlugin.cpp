/***********************************************************************************
** MIT License                                                                    **
**                                                                                **
** Copyright (c) 2018 Victor DENIS (victordenis01@gmail.com)                      **
**                                                                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
***********************************************************************************/

#include "StrateonPlugin.hpp"

#include "StrateonSideBar.hpp"
#include "StrateonToolButton.hpp"

#include "Application.hpp"

#include "Core/MainWindow.h"

StrateonPlugin::StrateonPlugin()
{
	// Empty	
}

Sn::PluginProp StrateonPlugin::pluginProp()
{
	Sn::PluginProp props;

	props.name = "Strateon Plugin";
	props.info = "Strateon Text Editor";
	props.desc = "A powerful text editor for Sielo";
	props.icon = QIcon(":logo/icon.png").pixmap(32);
	props.version = "1.0.0";
	props.author = "Victor DENIS <victordenis01@gmail.com>";

	props.hasSettings = false;

	return props;
}

void StrateonPlugin::init(InitState state, const QString& settingsPath)
{
	m_sideBar = new StrateonSideBar(this);
	Sn::Application::instance()->addSidebar("strateon-sidebar", m_sideBar);
}

void StrateonPlugin::unload()
{
	Sn::Application::instance()->removeSidebar(m_sideBar);
	delete m_sideBar;
	m_sideBar = nullptr;

	foreach(StrateonToolButton* button, m_navigationBarButtons)
		delete button;
}

bool StrateonPlugin::testPlugin()
{
	return Sn::Application::currentVersion.contains("1.17");
}

void StrateonPlugin::populateWebViewMenu(QMenu* menu, Sn::WebView* view, const Sn::WebHitTestResult& result)
{
	if (qobject_cast<Sn::TabbedWebView*>(view)) {
		m_webView = qobject_cast<Sn::TabbedWebView*>(view);

		menu->addAction(tr("Open Strateon in New Tab"), this, &StrateonPlugin::openNewStrateonTab);
	}
}

QWidget* StrateonPlugin::navigationBarButton(Sn::TabWidget* tabWidget)
{
	StrateonToolButton* button{new StrateonToolButton(tabWidget)};
	m_navigationBarButtons.append(button);

	return button;
}

void StrateonPlugin::openNewStrateonTab()
{
	if (!m_webView)
		return;

	MainWindow* window{new MainWindow()};

	m_webView->tabWidget()->addApplication(window);
}
