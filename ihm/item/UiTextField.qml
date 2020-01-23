import QtQuick 2.12
import QtQuick.Controls 2.3

TextField {
	id: rootItem;
	property int minWidth: Math.max(contentWidth, implicitWidth);
	property int minHeight: Math.max(contentHeight, implicitHeight);

	onFocusChanged: {
		if (focus) {
			selectAll();
		}
	}
}
