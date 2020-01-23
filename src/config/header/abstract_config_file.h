#ifndef ABSTRACT_CONFIG_FILE_H
#define ABSTRACT_CONFIG_FILE_H

#include <QObject>
#include <QDomDocument>
#include <QDomElement>

#include <QQmlEngine>
#include "factory_default_config.h"
#include "simple_crypt.h"

class AbstractConfigFile : public QObject
{
	Q_OBJECT
public:

	enum EnCheckMarkupResult{
		CeCmrWrongElement		= 0,
		CeCmrGoodEltNoneId		= CHECK_MARKUP_MASK_ELEMENT,
		CeCmrGoodEltIdUnwanted	= CHECK_MARKUP_MASK_ELEMENT | CHECK_MARKUP_MASK_ELT_ID,
		CeCmrGoodEltNoId		= CHECK_MARKUP_MASK_ELEMENT | CHECK_MARKUP_MASK_WANT_ID,
		CeCmrGoodEltWrongId		= CHECK_MARKUP_MASK_ELEMENT | CHECK_MARKUP_MASK_WANT_ID | CHECK_MARKUP_MASK_ELT_ID,
		CeCmrGoodEltAndId		= CHECK_MARKUP_MASK_ELEMENT | CHECK_MARKUP_MASK_WANT_ID | CHECK_MARKUP_MASK_ELT_ID | CHECK_MARKUP_MASK_IDS_MATCH
	};

	Q_PROPERTY(QString id READ id NOTIFY idChanged)
	Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)

	explicit AbstractConfigFile(QObject * parent = nullptr);
	AbstractConfigFile(const AbstractConfigFile & src);
	~AbstractConfigFile();

	virtual bool init(QDomElement & element, bool status = false, const QString & id = QString()) = 0;
	virtual QDomElement save(QDomDocument & doc) = 0;
//	static void RegisterClass();
	static EnCheckMarkupResult checkMarkup(QDomElement & element, const QString & markup, const QString & wantedId, QString * elementId = nullptr);

	QString id() const;

	bool isValid() const;

	SimpleCrypt * crypto() const;

signals:
	void idChanged(const QString & value);
	void isValidChanged(bool value);
	void configChanged();

public slots:

protected:
	static bool checkMarkup(QDomElement & element, const QString & markup, const QString & wantedId);
	bool checkMarkupAndSetId(QDomElement & element, const QString & markup, const QString & wantedId);
	void setIdToElement(QDomElement & element);
	void updateOrCreateAttibute(QDomElement & element, const QString & attrName, int value);
	void updateOrCreateAttibute(QDomElement & element, const QString & attrName, const QString & value);
	void setId(const QString & id);
	void setIsValid(bool value);

	static QString	m_markupTag;

private:
	QString			m_id;
	bool			m_isValid;
	SimpleCrypt		* m_crypto;
};

#endif // ABSTRACT_CONFIG_FILE_H
