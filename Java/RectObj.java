import java.awt.Rectangle;
import java.awt.Color;
import java.util.Random;

public class RectObj extends Rectangle{
    public Color color;
    public int speed = 0;
    public int rotation = 0;

    public RectObj(int x, int y, int width, int height){
        super(x, y, width, height);
        color = new Color(new Random().nextInt(255), new Random().nextInt(255), new Random().nextInt(255));
        speed = new Random().nextInt((6-2)+2);
    }
    public void update(){
        x = 2 + speed;
        rotation++;
        if(rotation >= 360){
            rotation = 0;
        }
    }
}