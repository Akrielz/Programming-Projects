using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Speech.Synthesis;

namespace WindowsFormsApplication4
{
    public partial class Form1 : Form
    {
        //Initializing the global variables.
        public int click = 0;
        public string[,] Tablero = new string[4,4];
        public int i;
        public int j;
        public int k = 9;
        public int win = 0;
        public int var;

        //This will welcome the user.
        SpeechSynthesizer synth = new SpeechSynthesizer();

        //Initializing a string which will check if there any X or O on vertical orizontals and diagonals.
        public string stringChecker;

        //Initializing a string helper which will help the string to check if it's true or false.
        public int checkerHelper;

        //Let's create a new functions which checks if somebody own.

        public Form1()
        {
            InitializeComponent();

            //This will welcome the user.
            synth.Speak("Welcome to Tic Tac Toe ,one point one , made by Akriel");
        }

        private void playerTurn_Click(object sender, EventArgs e)
        {
            
        }
        private void button1_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button1.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;
                if (click % 2 == 0)
                {

                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button1.Text == "")
            {
                if (click % 2 == 1)
                {
                    button1.Text = "X";
                    Tablero[1, 1] = "X";
                }
                else
                {
                    button1.Text = "O";
                    Tablero[1, 1] = "O";
                }
            }


            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var=0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if(Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                        Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        k = 9;
            }

        }
        private void button2_Click(object sender, EventArgs e)
        {

            //This will display player turn.
            if (button2.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }    

            //This will display the correct patern
            if (button2.Text == "")
            {
                if (click % 2 == 1)
                {
                    button2.Text = "X";
                    Tablero[1, 2] = "X";
                }
                else
                {
                    button2.Text = "O";
                    Tablero[1, 2] = "O";

                }

            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button3.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button3.Text == "")
            {
                if (click % 2 == 1)
                {
                    button3.Text = "X";
                    Tablero[1, 3] = "X";
                }
                else
                {
                    button3.Text = "O";
                    Tablero[1, 3] = "O";
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button4.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button4.Text == "")
            {
                if (click % 2 == 1)
                {
                    button4.Text = "X";
                    Tablero[2, 1] = "X";
                }
                else
                {
                    button4.Text = "O";
                    Tablero[2, 1] = "O";
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button5.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button5.Text == "")
            {
                if (click % 2 == 1)
                {
                    button5.Text = "X";
                    Tablero[2, 2] = "X";
                }
                else
                {
                    button5.Text = "O";
                    Tablero[2, 2] = "O";
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            //This will display player turn.
            if (button6.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;
                if (click % 2 == 0)
                {

                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button6.Text == "")
            {
                if (click % 2 == 1)
                {
                    button6.Text = "X";
                    Tablero[2, 3] = "X";
                }
                else
                {
                    button6.Text = "O";
                    Tablero[2, 3] = "O";
                }
            }

            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button7.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button7.Text == "")
            {
                if (click % 2 == 1)
                {
                    button7.Text = "X";
                    Tablero[3, 1] = "X";
                    win = 0;
                }
                else
                {
                    button7.Text = "O";
                    Tablero[3, 1] = "O";
                    win = 0;
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }

        }

        private void button8_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button8.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button8.Text == "")
            {
                if (click % 2 == 1)
                {
                    button8.Text = "X";
                    Tablero[3, 2] = "X";
                }
                else
                {
                    button8.Text = "O";
                    Tablero[3, 2] = "O";
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1; 
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            //This will display player turn.
            if (button9.Text == "")
            {
                //Same as before
                click++;
                k--;
                win = 0;

                if (click % 2 == 0)
                {
                    playerTurn.Text = "Player Turn: X";
                }
                else
                {
                    playerTurn.Text = "Player Turn: O";
                }
            }

            //This will display the correct patern
            if (button9.Text == "")
            {
                if (click % 2 == 1)
                {
                    button9.Text = "X";
                    Tablero[3, 3] = "X";
                }
                else
                {
                    button9.Text = "O";
                    Tablero[3, 3] = "O";
                }
            }
            //Making the program to check the orizontals.
            stringChecker = "X";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: X";
                        click = 0;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principal diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player X has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: X";
                    click = 0;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            stringChecker = "O";
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[i, j])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the vericals
            for (int i = 1; i <= 3; i++)
            {
                checkerHelper = 0;
                for (int j = 1; j <= 3; j++)
                {
                    if (stringChecker == Tablero[j, i])
                        checkerHelper++;

                    if (checkerHelper == 3)
                    {
                        Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                        //This will reinitializize the game.
                        button1.Text = "";
                        button2.Text = "";
                        button3.Text = "";
                        button4.Text = "";
                        button5.Text = "";
                        button6.Text = "";
                        button7.Text = "";
                        button8.Text = "";
                        button9.Text = "";
                        playerTurn.Text = "Player Turn: O";
                        click = 1;
                        for (int z = 1; z <= 3; z++)
                            for (int x = 1; x <= 3; x++)
                                Tablero[z, x] = "";
                        win = 1;
                        k = 9;
                    }
                }
            }
            //Making this program to check the principaly diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            //Making this program to check the secondrary diagonal
            checkerHelper = 0;
            for (int i = 1; i <= 3; i++)
            {
                if (stringChecker == Tablero[i, 4 - i])
                    checkerHelper++;

                if (checkerHelper == 3)
                {
                    Custom_Message_Box.Show("Player O has won.", "Winner!", "Okay");

                    //This will reinitializize the game.
                    button1.Text = "";
                    button2.Text = "";
                    button3.Text = "";
                    button4.Text = "";
                    button5.Text = "";
                    button6.Text = "";
                    button7.Text = "";
                    button8.Text = "";
                    button9.Text = "";
                    playerTurn.Text = "Player Turn: O";
                    click = 1;
                    for (int z = 1; z <= 3; z++)
                        for (int x = 1; x <= 3; x++)
                            Tablero[z, x] = "";
                    win = 1;
                    k = 9;
                }
            }
            var = 0;
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    if (Tablero[i, j] != "X" && Tablero[i, j] != "O")
                        var++;
            if (var == 0 && win == 0)
            {
                Custom_Message_Box.Show("It's a draw, you're both out of moves.", "Draw!", "Okay");

                //This will reinitializize the game.
                button1.Text = "";
                button2.Text = "";
                button3.Text = "";
                button4.Text = "";
                button5.Text = "";
                button6.Text = "";
                button7.Text = "";
                button8.Text = "";
                button9.Text = "";
                playerTurn.Text = "Player Turn: X";
                click = 0;
                for (int z = 1; z <= 3; z++)
                    for (int x = 1; x <= 3; x++)
                        Tablero[z, x] = "";
                k = 9;
            }
        }

        private void newGame_Click(object sender, EventArgs e)
        {
            //This will reinitializize the game.
            button1.Text = "";
            button2.Text = "";
            button3.Text = "";
            button4.Text = "";
            button5.Text = "";
            button6.Text = "";
            button7.Text = "";
            button8.Text = "";
            button9.Text = "";
            playerTurn.Text = "Player Turn: X";
            click = 0;
            for (int z = 1; z <= 3; z++)
                for (int x = 1; x <= 3; x++)
                    Tablero[z, x] = "";
            k = 9;
        }

    }
}
