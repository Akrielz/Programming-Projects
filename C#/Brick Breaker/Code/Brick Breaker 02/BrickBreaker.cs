using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Brick_Breaker_02
{
    public partial class BrickBreaker : Form
    {
        const int leftMargin = 0;
        const int rightMargin = 825;
        const int topMargin = 0;
        const int bottomMargin = 1000;

        const int playerWide = 245;
        const int playerCenter = playerWide / 2;

        int xDirection = 1;
        int yDirection = -1;

        int ballSpeed = 7;
        const int ballWide = 64;
        const int ballHeight = 68;

        bool ready = false;
        bool won = false;

        const int totalBlocks = 48;
        int currentBlocks;

        PictureBox[] Blocks;

        Random randomSeed = new Random();

        Point mouse;
        protected override void OnMouseMove(MouseEventArgs capturedMouse)
        {
            base.OnMouseMove(capturedMouse);
            mouse.X = capturedMouse.X - playerCenter;
            mouse.Y = capturedMouse.Y - playerCenter;

            if (mouse.X > leftMargin && mouse.X < rightMargin - playerWide)
                Player.Left = mouse.X;
        }
        public BrickBreaker()
        {
            InitializeComponent();
        }

        private void restartGame()
        {
            currentBlocks = totalBlocks;
            for (int index = 0; index < totalBlocks; index++)
            {
                if (Blocks[index].Top < topMargin)
                {
                    Blocks[index].Top += 500;
                    Blocks[index].Show();
                }
            }
            Ball.Top = Player.Top - 100;
            Ball.Left = Player.Left + playerCenter;
            int randomXDirection = randomSeed.Next(0,2);
            if (randomXDirection == 0)
                xDirection = 1;
            else
                xDirection = -1;
            yDirection = -1;
            ready = false;
            won = false;
            labelWin.Hide();
            labelAnyKey.Hide();
            Ball.Show();
            ballMovement.Start();
        }

        private void BrickBreaker_Load(object sender, EventArgs e)
        {
            Cursor.Hide();
            labelWin.Hide();
            currentBlocks = totalBlocks;
            Ball.Hide();
            int randomXDirection = randomSeed.Next(0, 2);
            if (randomXDirection == 0)
                xDirection = 1;
            else
                xDirection = -1;

            Blocks = new PictureBox[]
                {pictureBox1, pictureBox2, pictureBox3, pictureBox4, pictureBox5, pictureBox6, pictureBox7, pictureBox8, pictureBox9, pictureBox10,
            pictureBox11, pictureBox12, pictureBox13, pictureBox14, pictureBox15, pictureBox16, pictureBox17, pictureBox18, pictureBox19, pictureBox20,
            pictureBox21, pictureBox22, pictureBox23, pictureBox24, pictureBox25, pictureBox26, pictureBox27, pictureBox28, pictureBox29, pictureBox30,
            pictureBox31, pictureBox32, pictureBox33, pictureBox34, pictureBox35, pictureBox36, pictureBox37, pictureBox38, pictureBox39, pictureBox40,
            pictureBox41, pictureBox42, pictureBox43, pictureBox44, pictureBox45, pictureBox46, pictureBox47, pictureBox48 };
        }

        private void ballMovement_Tick(object sender, EventArgs e)
        {
            bool trigger = false;
            if (Ball.Left < leftMargin || Ball.Left + ballWide > rightMargin)
                xDirection *= -1;

            if (Ball.Top < topMargin)
                yDirection *= -1;

            if (Ball.Bounds.IntersectsWith(Player.Bounds) && yDirection == 1)
                yDirection *= -1;

            if (Ball.Top > bottomMargin + 50)
            {
                ballSpeed = 7;
                labelWin.Text = "You lost!";
                labelWin.Show();
                won = true;
                labelAnyKey.Text = "Press any key to restart";
                labelAnyKey.Show();
                ballMovement.Stop();
            }

            for ( int index = 0; index < totalBlocks; index++ )
                if ( Ball.Bounds.IntersectsWith(Blocks[index].Bounds) )
                {
                    if (Ball.Left < Blocks[index].Left || Ball.Right > Blocks[index].Right)
                        xDirection *= -1;
                    else
                    if (Ball.Bottom > Blocks[index].Bottom || Ball.Top < Blocks[index].Top )
                        yDirection *= -1;

                    Blocks[index].Hide();
                    Blocks[index].Top -= 500;
                    currentBlocks--;

                    if (currentBlocks == 36 || currentBlocks == 24 || currentBlocks == 12 || currentBlocks == 6)
                        ballSpeed += 2;

                    if (currentBlocks == 0)
                    {
                        labelWin.Text = "You won!";
                        labelWin.Show();
                        Ball.Hide();
                        won = true;
                        labelAnyKey.Text = "Press any key to restart";
                        labelAnyKey.Show();
                        ballMovement.Stop();
                    }
                }

            Ball.Left += ballSpeed * xDirection;
            Ball.Top += ballSpeed * yDirection;
        }

        private void BrickBreaker_KeyDown(object sender, KeyEventArgs e)
        {
            if (!ready)
            {
                ready = true;
                labelAnyKey.Hide();
                ballMovement.Start();
                Ball.Left = Player.Left + playerCenter;
                Ball.Show();
            }

            if (won)
                restartGame();
                
        }
    }
}
