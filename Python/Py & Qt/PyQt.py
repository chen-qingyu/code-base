import sys
from PyQt6 import QtWidgets, QtGui, QtCore

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QWidget()
    window.setWindowTitle("Hello PyQt")
    window.setWindowIcon(QtGui.QIcon("heart.ico"))
    window.resize(400, 300)
    window.show()

    text = QtWidgets.QLabel("Hello PyQt6!")
    text.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
    button = QtWidgets.QPushButton("Click me!")
    button.clicked.connect(lambda: QtWidgets.QMessageBox.information(window, "Hi", "Yoooo~"))
    layout = QtWidgets.QVBoxLayout()
    layout.addWidget(text)
    layout.addWidget(button)
    window.setLayout(layout)

    sys.exit(app.exec())
