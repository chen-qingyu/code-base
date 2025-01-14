package my.chat;

import javax.swing.*;
import java.awt.*;

public class Window extends JFrame
{
    // 文本域
    private final JTextArea textArea;
    // 滚动条
    private final JScrollPane scrollPane;
    // 面板
    private final JPanel panel;
    // 文本框
    private final JTextField textField;
    // 按钮
    private final JButton button;

    public JTextArea getTextArea()
    {
        return textArea;
    }

    public JScrollPane getScrollPane()
    {
        return scrollPane;
    }

    public JPanel getPanel()
    {
        return panel;
    }

    public JTextField getTextField()
    {
        return textField;
    }

    public JButton getButton()
    {
        return button;
    }

    public Window(String title, Point start)
    {
        // 初始化五个组件
        textArea = new JTextArea();
        textArea.setEditable(false);
        scrollPane = new JScrollPane();
        panel = new JPanel();
        textField = new JTextField(10);
        button = new JButton("发送");

        // 布局
        scrollPane.setViewportView(textArea);
        panel.add(textField);
        panel.add(button);
        this.add(scrollPane, BorderLayout.CENTER);
        this.add(panel, BorderLayout.SOUTH);

        // 配置
        this.setTitle(title);
        this.setSize(300, 300);
        this.setLocation(start);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public void showLine(String line)
    {
        textArea.append(line + System.lineSeparator());
    }
}
