package my.chat;

import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.*;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Properties;

public class Client
{
    public Client()
    {
        Window window = new Window("聊天程序 客户端", new Point(300, 300));

        try
        {
            // 1. Open socket
            Properties properties = new Properties();
            int clientPort = 0;
            String clientIP = null;
            try
            {
                properties.load(new FileReader("./chat.properties"));
                clientPort = Integer.parseInt(properties.getProperty("clientPort"));
                clientIP = properties.getProperty("clientIP");
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
            Socket socket = new Socket(clientIP, clientPort);

            // 2. Input/Output
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            // when button pressed, write output
            window.getButton().addActionListener((ActiveEvent) -> sendMessage(window, writer));
            // when 'Enter' pressed, write output
            window.getTextField().addKeyListener(new KeyAdapter()
            {
                @Override
                public void keyPressed(KeyEvent e)
                {
                    if (e.getKeyCode() == KeyEvent.VK_ENTER)
                    {
                        sendMessage(window, writer);
                    }
                }
            });

            String line;
            while ((line = reader.readLine()) != null)
            {
                // show socket input
                window.showLine(line);
            }

            // 3. Close socket
            socket.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    private void sendMessage(Window window, BufferedWriter writer)
    {
        // 1. 获取发送内容
        StringBuilder buffer = new StringBuilder();
        String text = window.getTextField().getText();
        buffer.append(text);
        // 2. 添加头数据
        buffer.insert(0, "客户端：");
        buffer.insert(0, new SimpleDateFormat("yyyy/MM/dd HH:mm:ss ").format(Calendar.getInstance().getTime()));
        text = buffer + System.lineSeparator();
        // 3. 自己文本域显示
        window.getTextArea().append(text);
        // 4. 发送
        try
        {
            writer.write(text);
            writer.flush();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        // 5. 清空文本框
        window.getTextField().setText("");
    }
}
