#include "StdAfx.h"
#include "hgLogExpand.h"

#include "frame/vtsLog.h"

static QtMessageHandler s_qtDefaultHandler = nullptr;

bool hgLogExpand::init(/* const char* logFile*/ )
{
	qInstallMessageHandler(0);
	s_qtDefaultHandler = qInstallMessageHandler(hgLogExpand::defaultMessageOutput);

	return true;
}

bool hgLogExpand::deInit()
{
	qInstallMessageHandler(0);
	return true;
}

void hgLogExpand::defaultMessageOutput( QtMsgType type, const QMessageLogContext& context, const QString& msg )
{
	vtsDebug << msg;
}