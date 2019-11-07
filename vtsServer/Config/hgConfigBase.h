#ifndef HG_CONFIGBASE_H_
#define HG_CONFIGBASE_H_

#include <QtCore/QSettings>
//#include <QColor>

class hgConfigBase
{
public:
	hgConfigBase(const QString& path, QSettings::Format format = QSettings::IniFormat, QObject* parent = NULL);
	~hgConfigBase(void);

	QString GetPath() const { return m_pSettings->fileName(); }

	bool GetValue(const QString& type, QString& value);
	//bool GetValue(const QString& type, QColor& value);
	bool GetValue(const QString& type, double& value);
	bool GetValue(const QString& type, int& value);
	bool GetValue(const QString& type, float& value);

    bool SetValue(const QString& type, const QVariant &value);
    bool AddValue(const QString& type, const QVariant &value);

private:
    QSettings* m_pSettings;
    QString m_path;
    QStringList m_allKeys;
};

#endif //HG_CONFIGBASE_H_