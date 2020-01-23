import QtQuick 2.0
import QtQuick.Controls 2.3

Label {
	id: rootItem;
	property int minWidth: Math.max(contentWidth, implicitWidth);
	property int minHeight: Math.max(contentHeight, implicitHeight);

	verticalAlignment: Text.AlignVCenter
}
