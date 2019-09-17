using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication3
{
    public partial class HangMan : Form
    {
        Random randomSeed = new Random();

        Point hangPoint, firstCorner, secondCorner;

        Graphics drawArea;

        List <string> possibleWords = new List<string>();

        List<char> usedLetters;

        List<char> displayedWord;

        string chosenWord;

        int lives, requiredLetters;

        public void erase(Point first, Point second)
        {
            Rectangle filledRectangle = new Rectangle(first.X, first.Y, second.X, second.Y);
            SolidBrush whiteBrush = new SolidBrush(Color.White);
            drawArea.FillRectangle(whiteBrush, filledRectangle);
        }

        public void drawHang(PaintEventArgs graphicPanel, int wide = 10)
        {
            Pen blackPen = new Pen(Color.Black, wide);

            Point first = new Point(50, 400);
            Point second = new Point(first.X+100, first.Y);

            Point third = new Point(first.X, first.Y - 40);
            Point fourth = new Point(second.X, third.Y);

            Point middle = new Point((third.X + fourth.X) / 2, fourth.Y);

            Point top1 = new Point(middle.X, middle.Y - 300);
            Point top2 = new Point(top1.X + 100, top1.Y);

            Point final = new Point(top2.X, top2.Y + 40);

            hangPoint = final;

            drawArea.DrawLine(blackPen, first, third);
            drawArea.DrawLine(blackPen, second, fourth);
            drawArea.DrawLine(blackPen, third, fourth);
            drawArea.DrawLine(blackPen, middle, top1);
            drawArea.DrawLine(blackPen, top1, top2);
            drawArea.DrawLine(blackPen, top2, final);
        }

        public void drawHuman(int wide = 10)
        {
            Pen blackPen = new Pen(Color.Black, wide);

            Point head = new Point(hangPoint.X-75/2, hangPoint.Y);

            Point neck = new Point(head.X+(75/2), head.Y+75);
            Point leftArm = new Point(neck.X - 50, neck.Y + 50);
            Point rightArm = new Point(neck.X + 50, leftArm.Y);

            Point bottom = new Point(neck.X, neck.Y + 100);
            Point leftLeg = new Point(bottom.X - 50, bottom.Y + 50);
            Point rightLeg = new Point(bottom.X + 50, leftLeg.Y);

            firstCorner.X = leftLeg.X-5;
            firstCorner.Y = head.Y-5;

            secondCorner.X = rightLeg.X+5;
            secondCorner.Y = rightLeg.Y+5;

            switch (lives)
            {
                case 5:
                    drawArea.DrawEllipse(blackPen, head.X, head.Y, 75, 75);
                    break;
                case 4:
                    drawArea.DrawLine(blackPen, neck, bottom);
                    break;
                case 3:
                    drawArea.DrawLine(blackPen, neck, leftArm);
                    break;
                case 2:
                    drawArea.DrawLine(blackPen, neck, rightArm);
                    break;
                case 1:
                    drawArea.DrawLine(blackPen, bottom, leftLeg);
                    break;
                case 0:
                    drawArea.DrawLine(blackPen, bottom, rightLeg);
                    break;
            }

        }

        public void printWord()
        {
            char[] buffer = new char[2*chosenWord.Length];
            for (int index = 0; index < chosenWord.Length; index++)
            {
                buffer[2 * index] = displayedWord[index];
                buffer[2 * index + 1] = ' ';
            }
            string result = new string(buffer);
            displayWordLabel.Text = result;
        }

        public void printUsedLetters()
        {
            char[] buffer = new char[2*usedLetters.Count];
            for (int index = 0; index < usedLetters.Count; index++)
            {
                buffer[2 * index] = usedLetters[index];
                if ( index != usedLetters.Count-1 )
                    buffer[2 * index + 1] = ',';
            }
            string result = new string(buffer);
            usedLettersLabel.Text = "Used letters:\n" + result;
        }

        public void readWordsFromFile()
        {
            StreamReader stream = new StreamReader("words.in");

            string data;
            while (true)
            {
                data = stream.ReadLine();
                if (data == null)
                    break;
                possibleWords.Add(data);
            }
        }

        public void chooseWord()
        {
            int position = randomSeed.Next(possibleWords.Count);
            chosenWord = possibleWords[position];
            chosenWord = chosenWord.ToUpper();
            displayedWord = new List<char>();
            for (int index = 0; index < chosenWord.Length; index++)
                displayedWord.Add('_');
        }

        public bool verifyLetter(char letter)
        {
            usedLetters.Add(letter);
            printUsedLetters();
            bool contained = false;
            for ( int index = 0; index < chosenWord.Length; index++)
            {
                if ( letter == chosenWord[index])
                {
                    contained = true;
                    displayedWord[index] = letter;
                    requiredLetters--;
                }
            }
            return contained;
        }

        public bool isInList(char letter)
        {
            foreach(char character in usedLetters)
            {
                if (character == letter)
                    return true;
            }
            return false;
        }

        public void resetVariables()
        {
            lives = 6;
            usedLetters = new List<char>();
            chooseWord();
            requiredLetters = chosenWord.Length;
            verifyLetter(chosenWord[0]);
            if ( isInList(chosenWord[chosenWord.Length - 1]) == false )
                verifyLetter(chosenWord[chosenWord.Length - 1]);
            printWord();
            erase(firstCorner, secondCorner);
            
        }

        public HangMan()
        {
            InitializeComponent();
            readWordsFromFile();
            drawArea = drawingArea.CreateGraphics();
            resetVariables();
        }

        private void Form1_Paint(object sender, PaintEventArgs graphicPanel)
        {
            drawHang(graphicPanel);
        }

        private void guessButton_Click(object sender, EventArgs e)
        {
            char givenLetter;
            string givenWord;

            givenWord = insertLetterBox.Text;
            if (givenWord.Length > 1)
            {
                MessageBox.Show("Please enter just a letter");
                insertLetterBox.Text = "";
                return;
            }

            if (givenWord.Length == 0)
            {
                MessageBox.Show("You must enter at least one letter before trying to guess");
                return;
            }

            givenWord = givenWord.ToUpper();
            givenLetter = givenWord[0];

            if ( !(givenLetter >= 'A' && givenLetter <= 'Z') ){
                MessageBox.Show("Your input must contain a letter");
                insertLetterBox.Text = "";
                return;
            }

            if ( isInList(givenLetter) )
            {
                MessageBox.Show("You have already used this letter");
                insertLetterBox.Text = "";
                return;
            }

            if (verifyLetter(givenLetter))
                printWord();
            else
            {
                lives--;
                drawHuman();
            }

            if (lives == 0)
            {
                MessageBox.Show("You lost");
                resetVariables();
            }

            if ( requiredLetters == 0 )
            {
                MessageBox.Show("You won");
                resetVariables();
            }

            insertLetterBox.Text = "";
        }

        private void restartButton_Click(object sender, EventArgs e)
        {
            resetVariables();
            insertLetterBox.Text = "";
        }
    }
}
