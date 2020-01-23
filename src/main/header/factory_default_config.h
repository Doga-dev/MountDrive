#ifndef FACTORY_DEFAULT_CONFIG_H
#define FACTORY_DEFAULT_CONFIG_H

#include <QDateTime>
#include <QDebug>
//"yyyy/MM/dd hh:mm:ss,zzz"
#define DEBUG_FULL_TIME							QDateTime::currentDateTime().toString("hh:mm:ss,zzz")

#define TRACE_FUNCTION_CALL						qDebug() << DEBUG_FULL_TIME << "¤ >> ¤" << Q_FUNC_INFO << "¤"
#define TRACE_DEBUG								qDebug() << DEBUG_FULL_TIME << "¤ ** ¤" << Q_FUNC_INFO << "¤"
#define TRACE_ERROR								qDebug() << DEBUG_FULL_TIME << "¤ !! ¤" << Q_FUNC_INFO << "¤"
#define TRACE_CLASS_CONSTRUCTOR					qDebug() << DEBUG_FULL_TIME << "¤ ++ ¤" << Q_FUNC_INFO << "¤"
#define TRACE_CLASS_DESTRUCTOR					qDebug() << DEBUG_FULL_TIME << "¤ -- ¤" << Q_FUNC_INFO << "¤"

#define DEF_H_WDGT_TITLE					64
#define DEF_W_WDGT_TITLE					128
#define DEF_H_WDGT_LABEL					48
#define DEF_W_WDGT_LABEL					96
#define DEF_H_WDGT_FIELD					48
#define DEF_W_WDGT_FIELD					128
#define DEF_H_WDGT_BUTTON					64
#define DEF_W_WDGT_BUTTON					256

// Application constant parameters

#define QML_LIBRARY_NAME					"DogaLib"
#define QML_LIBRARY_MAJ_VERSION			1
#define QML_LIBRARY_MIN_VERSION			0

#define PASSWORD_ENCRYPTION_KEY			"DOGA_ProductiveSolutions"

#define DATABASE_TYPE						"QSQLITE"
#define DATABASE_NAME						"dogabox.db"

#define APPLI_ABSOLUTE_PATH_TAG			"%AppAbsPath%"
#define USER_PICTURE_PATH					"file:///" APPLI_ABSOLUTE_PATH_TAG "/image/"

#define DRIVER_DO_NOTHING					"nop"
#define DEVICE_INFO_FIELD_NAME			"DeviceInfo"

#define FDC_POOLING_TIMING				100		// ms

#define DEFAULT_CONFIG_FILENAME			"app.config.xml"
#define CHECK_MARKUP_MASK_ELEMENT		0x01
#define CHECK_MARKUP_MASK_WANT_ID		0x02
#define CHECK_MARKUP_MASK_ELT_ID		0x04
#define CHECK_MARKUP_MASK_IDS_MATCH		0x08


// Default values

#define DEFAULT_TOLERANCE_X				"500"
#define DEFAULT_TOLERANCE_Y				"400"
#define DEFAULT_TOLERANCE_A				"200"

#define DEFAULT_BACKGROUND_COLOR		"white"
#define DEFAULT_FOREGROUND_COLOR		"black"
#define DEFAULT_BORDER_COLOR				"transparent"


// markup tags
#define MARKUP_TAG_APPLICATION			"application"
#define MARKUP_TAG_COLOR					"color"
#define MARKUP_TAG_COLOR_PALETTE		"colorPalette"
#define MARKUP_TAG_CONFIGURATION		"configuration"
#define MARKUP_TAG_DEFAULT_TOLERANCE	"defaultTolerance"
#define MARKUP_TAG_DEVICE					"device"
#define MARKUP_TAG_DEVICES				"devices"
#define MARKUP_TAG_FIELD					"field"
#define MARKUP_TAG_FILE_CONFIG			"fileConfig"
#define MARKUP_TAG_FOLDER_PATH			"folderPath"
#define MARKUP_TAG_LANGUAGE				"language"
#define MARKUP_TAG_NETWORK_CONNECTION	"networkConnection"
#define MARKUP_TAG_PARAMETERS			"parameters"
#define MARKUP_TAG_PATHS					"paths"
#define MARKUP_TAG_TIMING					"timing"
#define MARKUP_TAG_TOLERANCE				"tolerance"
#define MARKUP_TAG_WIDGET_COLORS		"widgetColors"
//#define MARKUP_TAG_						""

// attibute tags
#define ATTRIBUTE_TAG_BACKGROUND		"bkgd"
#define ATTRIBUTE_TAG_BORDER				"brdr"
#define ATTRIBUTE_TAG_COLUMN				"column"
#define ATTRIBUTE_TAG_FILENAME_FORMAT	"filenameFormat"
#define ATTRIBUTE_TAG_FIRST_DATA_ROW	"firstDataRow"
#define ATTRIBUTE_TAG_FOREGROUND		"frgd"
#define ATTRIBUTE_TAG_ID					"id"
#define ATTRIBUTE_TAG_IP_ADDRESS		"ip"
#define ATTRIBUTE_TAG_ISO_LANGUAGE		"iso"
#define ATTRIBUTE_TAG_LOGIN				"login"
#define ATTRIBUTE_TAG_MAXIMUM			"max"
#define ATTRIBUTE_TAG_MINIMUM			"min"
#define ATTRIBUTE_TAG_PASSWORD			"pwd"
#define ATTRIBUTE_TAG_PORT				"port"
#define ATTRIBUTE_TAG_TYPE				"type"
#define ATTRIBUTE_TAG_VALUE				"value"
#define ATTRIBUTE_TAG_VERSION			"version"
//#define ATTRIBUTE_TAG_					""


#endif // FACTORY_DEFAULT_CONFIG_H
