// Bibliotecas necessárias
import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Font;
import java.awt.image.BufferStrategy;
import java.awt.Color;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JFrame;

public class Game extends Canvas implements Runnable,MouseListener{

    public static final int WIDTH = 640, HEIGHT = 480;         // Dimensoes do game
    public static int contador = 100;                          // Contador de HP
    public static int pontuacao = 0;
    public static int mx, my;                                  // Ultimas posicoes do mouse
    public static boolean clicado = false;                     // Registrador do clique
    public boolean gameOver = false;

    public Spawner spawner;

    public Game(){
        Dimension dimension = new Dimension(WIDTH, HEIGHT);
        this.setPreferredSize(dimension);
        this.addMouseListener(this);
        spawner = new Spawner();
    }

    // Logica do game
    public void update(){
        spawner.update();
        // contador--;
        if(gameOver == false){
            if(contador <= 0){
                contador = 100;
                gameOver = true;
            }
        }
    }
    public void render(){
        BufferStrategy bs = this.getBufferStrategy();
        if (bs == null){ this.createBufferStrategy(3); return; }
        Graphics g = bs.getDrawGraphics();
        g.setColor(Color.black);
        g.fillRect(0, 0, WIDTH, HEIGHT);

        if(gameOver == false){
            g.setColor(Color.green);
            g.fillRect(Game.WIDTH/2 - 100 - 70, 20, contador*3, 20);
            g.setColor(Color.white);
            g.drawRect(Game.WIDTH/2 - 100 - 70, 20, 300, 20);
            
            spawner.render(g);
        } else {
            g.setColor(Color.white);
            g.setFont(new Font("Arial", Font.BOLD, 30));
            g.drawString("Game Over", WIDTH/2 - 100, HEIGHT/2 - 200);
            g.drawString("Your Score: " + pontuacao, WIDTH/2 - 120, HEIGHT/2 - 150);
            g.drawString(">> Press ENTER to play again <<", WIDTH/2 - 270, HEIGHT/2 + 80);
        }
        bs.show();
    }
    public static void main(String[] args){
        Game game = new Game();
        JFrame jframe = new JFrame("Meu Jogo");                // Janela do game
        jframe.add(game);                                      // Implementando o game na janela
        jframe.pack();
        jframe.setLocationRelativeTo(null);
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.setVisible(true);
        new Thread(game).start();                              // Inicio do game
    }

    @Override
    public void run(){
        while(true){
            update(); render();                                // Logica e renderizacao do game
            try{ Thread.sleep(1000/60); }                      // Frames por segundo (60 FPS)
            catch (InterruptedException e){ e.printStackTrace(); }
        }
    }
    // Eventos do mouse
    @Override
    public void mouseClicked(MouseEvent e){
        // TODO
    }
    @Override
    public void mouseEntered(MouseEvent arg0){
        // TODO
    }
    @Override
    public void mouseExited(MouseEvent arg0){
        // TODO
    }
    @Override
    public void mousePressed(MouseEvent e){
        Game.clicado = true; mx = e.getX(); my = e.getY();
    }
    @Override
    public void mouseReleased(MouseEvent arg0){
        // TODO
    }
}