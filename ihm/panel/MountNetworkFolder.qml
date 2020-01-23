import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import DogaLib 1.0
import "../item"
//import "../page"
import "../panel"

Item {
	id: rootItem;
	implicitWidth: 800
	implicitHeight: 600

	property alias server:		teServer.text
	property alias domain:		teDomain.text
	property alias login:		teLogin.text
	property alias password:	tePassword.text
	property alias netDir:		teNetDir.text
	property alias mntDir:		teMountDir.text

	ProcessesManager {
		id: proc;
	}

	GridLayout {
		id: grid
		anchors.fill: parent
		columns: 2
		columnSpacing: 8
		rowSpacing: 8

		property double eltW: (rootItem.width * 0.5);	//- grid.columnSpacing * (grid.columns - 1)) / grid.columns
		property double eltH: (rootItem.height - grid.rowSpacing * (grid.rows - 1)) / grid.rows

		UiInputField {
			id: teServer
			labelText: qsTr("Nom du serveur")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			enabled: ! proc.isMounted
		}

		UiInputField {
			id: teDomain
			labelText: qsTr("Domaine")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			enabled: ! proc.isMounted
		}

		UiInputField {
			id: teLogin
			labelText: qsTr("Identifiant")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			enabled: ! proc.isMounted
		}

		UiInputField {
			id: tePassword
			labelText: qsTr("Mot de passe")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			echoMode: TextInput.Password
			enabled: ! proc.isMounted
		}

		UiInputField {
			id: teNetDir
			labelText: qsTr("Chemin du répertoire")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			enabled: ! proc.isMounted
		}
		UiInputField {
			id: teMountDir
			labelText: qsTr("Point de montage")
			inputWidth: grid.eltW
			height: grid.eltH
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			text: proc.mountPoint
			enabled: ! proc.isMounted
		}

		UiButton {
			id: btMount;
			text: qsTr("Connecter")
			Layout.fillWidth: true;
			enabled: ! proc.isMounted
			onClicked: proc.startMountProcess(teServer.text, teDomain.text, teLogin.text, tePassword.text, teNetDir.text, teMountDir.text);
		}
		UiButton {
			id: btUmount;
			text: qsTr("Déconnecter")
			Layout.fillWidth: true;
			enabled: proc.isMounted
			onClicked: proc.startUmountProcess(teMountDir.text);
		}
//		UiButton {
//			id: btMountInfo;
//			text: qsTr("Informations")
////            Layout.columnSpan: 2
//			Layout.fillWidth: true;
//			onClicked: proc.logMountedDriveInfo(teMountDir.text);
//		}
		UiLabel {
			id: mountingState;
			text: proc.isMounted() ? qsTr("Connected") : qsTr("Unconnected")
			color: proc.isMounted() ? qsTr("green") : qsTr("red")
			Layout.columnSpan: 2
			Layout.fillWidth: true;
			horizontalAlignment: Text.AlignHCenter
		}
	}

}

/*##^##
Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
