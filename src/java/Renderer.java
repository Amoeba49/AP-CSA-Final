import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Renderer {

    public Renderer() {
        SwingUtilities.invokeLater(new GameWindow());
    }
}

class ImagePanel extends JPanel{

    private BufferedImage image;

    public ImagePanel() {
        image = new BufferedImage(640, 480, BufferedImage.TYPE_INT_RGB);
        int rgb = image.getRGB(320, 240);
        int r = (rgb>>16)&0xFF;
        int g = (rgb>>8)&0xFF;
        int b = (rgb)&0xFF;
        System.out.println(r + " " + g + " " + b);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, this);
    }

}

class GameWindow implements Runnable {
    @Override
    public void run() {
        JFrame frame = new JFrame("Engine");

        JPanel panel = new JPanel();
        panel.setBounds(0, 0, 640, 480);
        panel.add(new ImagePanel());

        frame.setContentPane(panel);
        frame.pack();
        frame.setVisible(true);
        System.out.println(frame.getContentPane());
    }
}