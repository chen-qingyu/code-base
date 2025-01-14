import os
import sys

from PySide6.QtCore import QDataStream, QFile, QIODevice, QDateTime, QTimer, QUrl
from PySide6.QtWidgets import QApplication, QWidget, QTableWidget, QHBoxLayout, QPushButton, QVBoxLayout, \
    QComboBox, QDateTimeEdit, QMessageBox, QLabel, QLineEdit, QHeaderView


def main():
    app = QApplication(sys.argv)

    _ = TodoTool()

    sys.exit(app.exec())


class TodoTool(QWidget):
    FILE = "./data.dat"
    COMBO = ["TODO", "进行中", "已完成", "已删除"]
    HEADER = ["状态", "事项", "开始时间", "截止时间"]

    def __init__(self):
        super().__init__()

        self.table = QTableWidget(0, len(self.HEADER))
        self.table.setHorizontalHeaderLabels(self.HEADER)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)
        self.table.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)

        if os.path.exists(self.FILE):
            self.read_data()

        self.timer = QTimer()
        self.timer.timeout.connect(self.check_todo)
        self.timer.start(1000 * 60)  # 1分钟

        self.init_ui()

    def init_ui(self):
        # widgets
        btn_add = QPushButton("Add todo")
        btn_remove = QPushButton("Remove deleted")
        btn_clear = QPushButton("Clear all")
        btn_help = QPushButton("Help")

        combo_filter = QComboBox()
        combo_filter.addItems(["全部"] + self.COMBO)

        edit_search = QLineEdit()

        # connects
        btn_add.clicked.connect(self.add)
        btn_remove.clicked.connect(self.remove)
        btn_clear.clicked.connect(self.clear)
        btn_help.clicked.connect(self.help)

        combo_filter.currentTextChanged.connect(self.refresh)

        edit_search.textChanged.connect(self.search)

        # layouts
        h_box = QHBoxLayout()
        h_box.addWidget(btn_add)
        h_box.addWidget(btn_remove)
        h_box.addWidget(btn_clear)
        h_box.addSpacing(10)
        h_box.addWidget(QLabel("显示状态："))
        h_box.addWidget(combo_filter)
        h_box.addSpacing(10)
        h_box.addWidget(QLabel("查找内容："))
        h_box.addWidget(edit_search)
        h_box.addStretch()
        h_box.addWidget(btn_help)

        v_box = QVBoxLayout()
        v_box.addLayout(h_box)
        v_box.addWidget(self.table)

        self.setWindowTitle("Todo Tool")
        self.resize(800, 600)
        self.setLayout(v_box)
        self.show()

    def add(self):
        row_cnt = self.table.rowCount()
        self.table.insertRow(row_cnt)

        combo = QComboBox()
        combo.addItems(self.COMBO)
        combo.currentIndexChanged.connect(self.save_data)
        self.table.setCellWidget(row_cnt, 0, combo)

        line = QLineEdit()
        line.textChanged.connect(self.save_data)
        self.table.setCellWidget(row_cnt, 1, line)

        start = QDateTimeEdit()
        start.dateTimeChanged.connect(self.save_data)
        self.table.setCellWidget(row_cnt, 2, start)

        end = QDateTimeEdit()
        end.dateTimeChanged.connect(self.save_data)
        self.table.setCellWidget(row_cnt, 3, end)

        self.save_data()

    def save_data(self):
        file = QFile(self.FILE)
        file.open(QIODevice.OpenModeFlag.WriteOnly)
        stream = QDataStream(file)
        row_cnt = self.table.rowCount()
        stream.writeInt32(row_cnt)
        for r in range(row_cnt):
            stream.writeInt32(self.table.cellWidget(r, 0).currentIndex())
            stream.writeString(self.table.cellWidget(r, 1).text())
            stream << QDateTime(self.table.cellWidget(r, 2).dateTime())
            stream << QDateTime(self.table.cellWidget(r, 3).dateTime())
        file.close()

    def read_data(self):
        file = QFile(self.FILE)
        file.open(QIODevice.OpenModeFlag.ReadOnly)
        stream = QDataStream(file)
        row_cnt = stream.readInt32()
        self.table.setRowCount(row_cnt)
        for r in range(row_cnt):
            combo = QComboBox()
            combo.addItems(self.COMBO)
            combo.setCurrentIndex(stream.readInt32())
            combo.currentIndexChanged.connect(self.save_data)
            self.table.setCellWidget(r, 0, combo)

            line = QLineEdit()
            line.setText(stream.readString())
            line.textChanged.connect(self.save_data)
            self.table.setCellWidget(r, 1, line)

            time = QDateTime()
            stream >> time
            start = QDateTimeEdit()
            start.setDateTime(time)
            start.dateTimeChanged.connect(self.save_data)
            self.table.setCellWidget(r, 2, start)

            time = QDateTime()
            stream >> time
            end = QDateTimeEdit()
            end.setDateTime(time)
            end.dateTimeChanged.connect(self.save_data)
            self.table.setCellWidget(r, 3, end)
        file.close()

    def remove(self):
        for r in range(self.table.rowCount() - 1, -1, -1):  # 必须从后往前删
            if self.table.cellWidget(r, 0).currentText() == "已删除":
                self.table.removeRow(r)
        self.save_data()

    def clear(self):
        self.table.clearContents()
        self.table.setRowCount(0)
        self.save_data()

    def refresh(self, status):
        for r in range(self.table.rowCount()):
            self.table.setRowHidden(r, status != "全部" and self.table.cellWidget(r, 0).currentText() != status)

    def search(self, string):
        for r in range(self.table.rowCount()):
            self.table.setRowHidden(r, self.table.cellWidget(r, 1).text().find(string) == -1)

    def check_todo(self):
        now = QDateTime.currentDateTime()

        for r in range(self.table.rowCount()):
            start = self.table.cellWidget(r, 2)
            end = self.table.cellWidget(r, 3)
            if start.dateTime().date() == now.date() \
                    and start.dateTime().time().hour() == now.time().hour() \
                    and start.dateTime().time().minute() == now.time().minute():
                btn = QMessageBox.information(self, "时间到了！", f"第{r + 1}行的待办事项开始时间到了，延迟十分钟吗？",
                                              QMessageBox.StandardButton.Ok | QMessageBox.StandardButton.Cancel)
                if btn == QMessageBox.StandardButton.Ok:
                    start.setDateTime(start.dateTime().addSecs(60 * 10))
            elif end.dateTime().date() == now.date() \
                    and end.dateTime().time().hour() == now.time().hour() \
                    and end.dateTime().time().minute() == now.time().minute():
                btn = QMessageBox.information(self, "时间到了！", f"第{r + 1}行的待办事项截止时间到了，延迟十分钟吗？",
                                              QMessageBox.StandardButton.Ok | QMessageBox.StandardButton.Cancel)
                if btn == QMessageBox.StandardButton.Ok:
                    end.setDateTime(end.dateTime().addSecs(60 * 10))

    def help(self):
        QMessageBox.information(self, "Help",
                                """
        Todo Tool -- Version 1.0
        
        1、用户可以在主界面添加待做事项
        2、每个待做事项可以按照类别编辑
        3、每次增加或改变数据后自动保存
        4、任何事项到达提醒时间进行提醒
        5、可以按类别显示不同状态的事项
        6、删除状态的事项可以完全清除掉
        7、可以输入关键字查询事项的内容
        """)


if __name__ == '__main__':
    main()
