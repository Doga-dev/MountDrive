import QtQuick 2.12
import QtQuick.Controls 2.3

Button {
	id: control
	text: qsTr("Bouton")
	states: [
		State {
			name: "disabled"; when: ! enabled;
			PropertyChanges {
				target: bkgd
				opacity: 0.3
			}
		}
	]
	background: Rectangle {
		id: bkgd
		implicitWidth: 100
		implicitHeight: 40
		opacity: 1
		color: control.down ? "#5ca0cd" : "#134980"
		border.color: "#EE1C25"
		border.width: 3
	}
	contentItem: Label {
		id: label
		text: control.text
		font: control.font
		color: control.down ? "#030000" : (control.focus ? "white" : "#b1b2b3")
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}
}
