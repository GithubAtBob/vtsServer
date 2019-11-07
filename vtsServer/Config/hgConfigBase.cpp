#include "StdAfx.h"
#include "Config/hgConfigBase.h"


hgConfigBase::hgConfigBase(const QString& path, QSettings::Format format /*= QSettings::IniFormat*/, QObject* parent /*= NULL*/)
{
	m_pSettings = new QSettings(path, format, parent);
    m_path = path;
    m_allKeys = m_pSettings->allKeys();
}


hgConfigBase::~hgConfigBase(void)
{
	if (m_pSettings != NULL)
	{
		delete m_pSettings;
		m_pSettings = NULL;
	}
}

bool hgConfigBase::GetValue(const QString& type, QString& value)
{
	if (!type.isEmpty())
	{
		value = m_pSettings->value(type).toString();
		return true;
	}
	return false;
}

bool hgConfigBase::GetValue(const QString& type, double& value)
{
	if (!type.isEmpty())
	{
		value = m_pSettings->value(type).toString().toDouble();
		return true;
	}
	return false;
}

bool hgConfigBase::GetValue(const QString& type, int& value)
{
	if (!type.isEmpty())
	{
		value = m_pSettings->value(type).toString().toInt();
		return true;
	}
	return false;
}

bool hgConfigBase::GetValue(const QString& type, float& value)
{
	if (!type.isEmpty())
	{
		value = m_pSettings->value(type).toString().toFloat();
		return true;
	}
	return false;
}

// bool hgConfigBase::GetValue(const QString& type, QColor& value)
// {
// 	if (!type.isEmpty())
// 	{
// 		QString l_strColor = m_pSettings->value(type).toString();
// 		QColor l_color;
// 		if (l_strColor.contains("#"))
// 		{
// 			l_color.setNamedColor(l_strColor);
// 		}
// 		else
// 		{
// 			l_strColor.remove('(');
// 			l_strColor.remove(')');
// 			QStringList l_strList = l_strColor.split(",");
// 			if (l_strList.count() >= 3)
// 			{
// 				int l_r = l_strList.at(0).toInt();
// 				int l_g = l_strList.at(1).toInt();
// 				int l_b = l_strList.at(2).toInt();
// 
// 				int l_a = 255;
// 				if (l_strList.count() == 4)
// 				{
// 					l_a = l_strList.at(3).toInt();
// 				}
// 				l_color.setRed(qRgba(l_r, l_g, l_b, l_a));
// 			}
// 		}
// 		value = l_color;
// 		return true;
// 	}
// 	return false;
// }

bool hgConfigBase::SetValue(const QString& type, const QVariant &value)
{
	if (!type.isEmpty())
	{
		m_pSettings->setValue(type,value);
		return true;
	}
	return false;
}

bool hgConfigBase::AddValue(const QString& type, const QVariant &value)
{
    if (!m_pSettings->contains(type))
    {
        m_pSettings->setValue(type,value);
        m_pSettings->sync();
        return true;
    }

    return false;
}
