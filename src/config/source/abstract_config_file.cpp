#include "abstract_config_file.h"
#include "configuration.h"
#include "tools.h"

AbstractConfigFile::AbstractConfigFile(QObject * parent) : QObject(parent)
  , m_id()
  , m_isValid(true)
  , m_crypto(nullptr)
{
	//TRACE_CLASS_CONSTRUCTOR;
	QObject::connect(this, & AbstractConfigFile::idChanged		, this, & AbstractConfigFile::configChanged);
	QObject::connect(this, & AbstractConfigFile::isValidChanged	, this, & AbstractConfigFile::configChanged);
	if (Configuration * cfg = qobject_cast<Configuration *>(parent)) {
		m_crypto = cfg->crypto();
	}
	if (AbstractConfigFile * acf = qobject_cast<AbstractConfigFile *>(parent)) {
		m_crypto = acf->crypto();
	}
}

AbstractConfigFile::AbstractConfigFile(const AbstractConfigFile & src) : QObject(src.parent())
  , m_id(src.m_id)
  , m_isValid(src.m_isValid)
{
	//TRACE_CLASS_CONSTRUCTOR;
	QObject::connect(this, & AbstractConfigFile::idChanged		, this, & AbstractConfigFile::configChanged);
	QObject::connect(this, & AbstractConfigFile::isValidChanged	, this, & AbstractConfigFile::configChanged);
}

AbstractConfigFile::~AbstractConfigFile()
{
	//TRACE_CLASS_DESTRUCTOR;
}

//void AbstractConfigFile::RegisterClass()
//{
//	qmlRegisterType<AbstractConfigFile>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, "ConfigItem");
//}

AbstractConfigFile::EnCheckMarkupResult AbstractConfigFile::checkMarkup(QDomElement & element, const QString & markup, const QString & wantedId, QString * elementId)
{
	EnCheckMarkupResult res = CeCmrWrongElement;

	if (element.tagName() == markup) {
		if (wantedId.isEmpty()) {
			if (element.hasAttribute(ATTRIBUTE_TAG_ID)) {
				if (elementId) {
					* elementId = element.attribute(ATTRIBUTE_TAG_ID);
				}
				res = CeCmrGoodEltIdUnwanted;
			} else {
				res = CeCmrGoodEltNoneId;
			}
		} else {
			if (element.hasAttribute(ATTRIBUTE_TAG_ID)) {
				if (elementId) {
					* elementId = element.attribute(ATTRIBUTE_TAG_ID);
				}
				if (wantedId == element.attribute(ATTRIBUTE_TAG_ID)) {
					res = CeCmrGoodEltAndId;
				} else {
					res = CeCmrGoodEltWrongId;
				}
			} else {
				res = CeCmrGoodEltNoId;
			}
		}
	}
	return res;
}

bool AbstractConfigFile::checkMarkup(QDomElement & element, const QString & markup, const QString & wantedId)
{
	bool res = ((element.tagName() == markup) && ((wantedId == "") || (wantedId == element.attribute(ATTRIBUTE_TAG_ID))));
//	TRACE_DEBUG << element.tagName() << markup << wantedId << element.attribute(ATTRIBUTE_TAG_ID) << res;
	return res;
}

bool AbstractConfigFile::checkMarkupAndSetId(QDomElement & element, const QString & markup, const QString & wantedId)
{
	bool ret = false;
	if ((element.tagName() == markup) && ((wantedId.isEmpty()) || (wantedId == element.attribute(ATTRIBUTE_TAG_ID)))) {
		setId(element.attribute(ATTRIBUTE_TAG_ID));
		ret = true;
	}
	return ret;
}

void AbstractConfigFile::setIdToElement(QDomElement & element)
{
	if (! m_id.isEmpty()) {
		updateOrCreateAttibute(element, ATTRIBUTE_TAG_ID, m_id);
	}
}

void AbstractConfigFile::updateOrCreateAttibute(QDomElement & element, const QString & attrName, int value)
{
	updateOrCreateAttibute(element, attrName, convIntToString(value));
}

void AbstractConfigFile::updateOrCreateAttibute(QDomElement & element, const QString & attrName, const QString & value)
{
	if (element.hasAttribute(attrName)) {
		element.removeAttribute((attrName));
	}
	element.setAttribute(attrName, value);
}

QString AbstractConfigFile::id() const
{
	return m_id;
}
void AbstractConfigFile::setId(const QString & id)
{
	if (m_id != id) {
		m_id = id;
		emit idChanged(m_id);
	}
}

void AbstractConfigFile::setIsValid(bool value)
{
		if (m_isValid != value) {
			m_isValid = value;
			emit isValidChanged(m_isValid);
		}

}

SimpleCrypt * AbstractConfigFile::crypto() const
{
	return m_crypto;
}

bool AbstractConfigFile::isValid() const
{
	return m_isValid;
}

