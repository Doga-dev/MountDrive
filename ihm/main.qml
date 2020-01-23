import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12
import "panel"

Window {
	visible: true
	width: 1280
	height: 800
	title: qsTr("Montage d'un répertoire partagé sur le réseau")

	RowLayout {
		id: rLayout
		anchors.fill: parent
		anchors.margins: 10
		spacing: 10

		MountNetworkFolder {
			id: panel1;
			Layout.fillHeight: true;
			Layout.fillWidth: true;
			server: "server"
			domain: "domain"
			login: "user"
			netDir: "Shared"
			mntDir: "M:/"
		}

		Rectangle {
			id: separator;
			color: "grey"
			Layout.fillHeight: true
			width: 4
		}

		MountNetworkFolder {
			id: panel2;
			Layout.fillHeight: true;
			Layout.fillWidth: true;
			server: "server"
			domain: "domain"
			login: "user"
			netDir: "Shared/Report"
			mntDir: "R:/"
		}
	}
}
