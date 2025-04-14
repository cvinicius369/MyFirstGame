import java.awt.Rectangle;
import java.awt.Color;
import java.util.Random;
import java.awt.Graphics;

public class Particula extends Rectangle{
    public Color color;
    public int speed = 0;
    public int rotation = 0;
    public int timer = 0;
    public double xa, ya;
    public double dx, dy;

    public Particula(int x, int y, int width, int height, Color color){
        super(x, y, width, height);
        xa = x;
        ya = y;
        this.color = color;
        dx = new Random().nextGaussian();
        dy = new Random().nextGaussian();
        speed = 8;
    }
    public void update(){
        x+=dx*speed;
        y+=dy*speed;
        timer++;
    }
    public void render(Graphics g){
        g.setColor(this.color);
        g.fillRect((int)xa, (int)ya, width, height);
    }
}