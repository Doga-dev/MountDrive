import QtQuick 2.12
import QtQuick.Layouts 1.3
import "../item"
//import "../page"
import "../panel"

Item {
	id: rootItem
	implicitWidth: hd.itmW;
	implicitHeight: hd.itmH;

	signal editingFinished()

	property alias text: tiInput.text
	property alias textFont: tiInput.font
	property alias horizontalAlignment: tiInput.horizontalAlignment
	property alias readOnly: tiInput.readOnly
	property alias echoMode: tiInput.echoMode
	property alias inputMethodHints: tiInput.inputMethodHints
	property alias inputMask: tiInput.inputMask

	property int labelPosition: Qt.LeftEdge
	property alias label: tLabel
	property alias labelText: tLabel.text
//	property alias labelHAlign: tLabel.horizontalAlignment
	property int labelHAlign: 0;
	property int labelWidth: -1;
	property int labelHeight: 0;
	property int inputWidth: 0;
	property int inputHeight: 0;
//	property alias labelWidth: tLabel.width

	onLabelHAlignChanged: {
		tLabel.horizontalAlignment = labelHAlign;
	}

	onLabelPositionChanged: {
		hd.setLabelPosition();
	}
	onLabelWidthChanged: {
		hd.setLabelPosition();
	}
	onInputWidthChanged: {
		hd.setLabelPosition();
	}
	onWidthChanged: {
		hd.setLabelPosition();
	}

	Item {
		id: hd
		property int margin: parent.height / 16
//		property WidgetColors fieldColor: tiInput.focus	? Palette.widget(ColorPalette.CeWidInpSel)
//														: tiInput.readOnly	? Palette.widget(ColorPalette.CeWidInpDim)
//																			: Palette.widget(ColorPalette.CeWidInpNrm)

//		property WidgetColors labelColor: tiInput.readOnly	? Palette.widget(ColorPalette.CeWidLblDim)
//															: Palette.widget(ColorPalette.CeWidLblNrm)
		property int lblX: 0;
		property int lblY: 0;
		property int lblW: 0;
		property int lblH: 0;

		property int inpX: 0;
		property int inpY: 0;
		property int inpW: 0;
		property int inpH: 0;

		property int itmW: 0;
		property int itmH: 0;	//tiInput.font.pixelSize * 2;

		function setLabelPosition() {
			var lbX = 0, lbY = 0, lbW = 0, lbH = 0;
			var inX = 0, inY = 0, inW = 0, inH = 0;
			var itW = 0, itH = 0;

			switch (rootItem.labelPosition) {
			case Qt.LeftEdge:
			case Qt.RightEdge:
				if (rootItem.width > 0) {
					itW = rootItem.width;
					if (rootItem.inputWidth > 0) {
						inW = rootItem.inputWidth;
						lbW = itW - inW;
					} else {
						if (rootItem.labelWidth >= 0) {
							lbW = rootItem.labelWidth;
						} else {
							lbW = tLabel.minWidth;
						}
						inW = itW - lbW;
					}
				} else {
					if (rootItem.labelWidth >= 0) {
						lbW = rootItem.labelWidth;
					} else {
						lbW = tLabel.width;
					}
					if (rootItem.inputWidth >= 0) {
						inW = rootItem.inputWidth;
					} else {
						inW = tiInput.minWidth;
					}
					itW = lbW + inW;
				}
				if (rootItem.height > 0) {
					itH = rootItem.height;
				} else {
					if (rootItem.labelHeight > 0) {
						lbH = rootItem.labelHeight;
					} else {
						lbH = tLabel.minHeight;
					}
					if (rootItem.inputHeight > 0) {
						inH = rootItem.inputHeight;
					} else {
						inH = tiInput.minHeight;
					}
					itH = Math.max(lbH, inH);	//, tLabel.font.pixelSize * 2, tiInput.font.pixelSize * 2);
				}
				lbH = itH;
				inH = itH;
				if (rootItem.labelHAlign === 0) {
					tLabel.horizontalAlignment = Text.AlignLeft;
				}
				break;
			case Qt.TopEdge:
			case Qt.BottomEdge:
				if (rootItem.height > 0) {
					itH = rootItem.height;
					if (rootItem.inputHeight > 0) {
						inH = rootItem.inputHeight;
						lbH = itH - inH;
					} else {
						if (rootItem.labelHeight > 0) {
							lbH = rootItem.labelHeight;
						} else {
							lbH = tLabel.minHeight;
						}
						inH = itH - lbH;
					}
				} else {
					if (rootItem.labelHeight > 0) {
						lbH = rootItem.labelHeight;
					} else {
						lbH = tLabel.minHeight;
					}
					if (rootItem.inputHeight > 0) {
						inH = rootItem.inputHeight;
					} else {
						inH = tiInput.minHeight;
					}
					itH = lbH + inH;
				}
				if (rootItem.width > 0) {
					itW = rootItem.width;
				} else{
					if (rootItem.labelWidth >= 0) {
						lbW = rootItem.labelWidth;
					} else {
						lbW = tLabel.minWidth;
					}
					if (rootItem.inputWidth >= 0) {
						inW = rootItem.inputWidth;
					} else {
						inW = tiInput.minWidth;
					}
					itW = Math.max(lbW, inW);
				}
				lbW = itW;
				inW = itW;
				if (rootItem.labelHAlign === 0) {
					tLabel.horizontalAlignment = Text.AlignHCenter;
				}
				break;
			}
			switch (rootItem.labelPosition) {
			case Qt.LeftEdge:
				inX = lbW;
				break;
			case Qt.TopEdge:
				inY = lbH;
				break;
			case Qt.RightEdge:
				lbX = inW;
				break;
			case Qt.BottomEdge:
				lbY = inH;
				break;
			}
			hd.lblX = lbX;
			hd.lblY = lbY;
			hd.inpX = inX;
			hd.inpY = inY;
			hd.itmW = itW;
			hd.itmH = itH;
			tLabel.width	= lbW;
			tLabel.height	= lbH;
			tiInput.width	= inW;
			tiInput.height	= inH;
		}
	}

	Component.onCompleted: {
		hd.setLabelPosition();
	}
	UiLabel {
		id: tLabel
		x: hd.lblX; y: hd.lblY;
		text: ""
		visible: text !== ""
		enabled: tiInput.readOnly
	}

	UiTextField {
		id: tiInput;
		x: hd.inpX; y: hd.inpY;
		text: ""

		onEditingFinished: rootItem.editingFinished
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
