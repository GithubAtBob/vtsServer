#pragma once

#include <functional>
#include <QString>

class hgLogExpand
{
public:
	static bool init( /*const char* logFile*/ );

	static bool deInit();

private:
	static void defaultMessageOutput( QtMsgType type,
		const QMessageLogContext& context, const QString& msg );

};