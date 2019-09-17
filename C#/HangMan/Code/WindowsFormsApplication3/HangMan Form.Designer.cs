namespace WindowsFormsApplication3
{
    partial class HangMan
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HangMan));
            this.insertLetterBox = new System.Windows.Forms.RichTextBox();
            this.guessButton = new System.Windows.Forms.Button();
            this.restartButton = new System.Windows.Forms.Button();
            this.drawingArea = new System.Windows.Forms.PictureBox();
            this.displayWordLabel = new System.Windows.Forms.Label();
            this.usedLettersLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.drawingArea)).BeginInit();
            this.SuspendLayout();
            // 
            // insertLetterBox
            // 
            this.insertLetterBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 35.25F);
            this.insertLetterBox.Location = new System.Drawing.Point(260, 599);
            this.insertLetterBox.Name = "insertLetterBox";
            this.insertLetterBox.Size = new System.Drawing.Size(70, 70);
            this.insertLetterBox.TabIndex = 2;
            this.insertLetterBox.Text = "";
            // 
            // guessButton
            // 
            this.guessButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 24.25F);
            this.guessButton.Location = new System.Drawing.Point(12, 599);
            this.guessButton.Name = "guessButton";
            this.guessButton.Size = new System.Drawing.Size(200, 70);
            this.guessButton.TabIndex = 3;
            this.guessButton.Text = "Guess";
            this.guessButton.UseVisualStyleBackColor = true;
            this.guessButton.Click += new System.EventHandler(this.guessButton_Click);
            // 
            // restartButton
            // 
            this.restartButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 24.25F);
            this.restartButton.Location = new System.Drawing.Point(1052, 599);
            this.restartButton.Name = "restartButton";
            this.restartButton.Size = new System.Drawing.Size(200, 70);
            this.restartButton.TabIndex = 4;
            this.restartButton.Text = "Try Again";
            this.restartButton.UseVisualStyleBackColor = true;
            this.restartButton.Click += new System.EventHandler(this.restartButton_Click);
            // 
            // drawingArea
            // 
            this.drawingArea.Location = new System.Drawing.Point(0, 0);
            this.drawingArea.Name = "drawingArea";
            this.drawingArea.Size = new System.Drawing.Size(506, 432);
            this.drawingArea.TabIndex = 5;
            this.drawingArea.TabStop = false;
            // 
            // displayWordLabel
            // 
            this.displayWordLabel.AutoSize = true;
            this.displayWordLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 28.25F);
            this.displayWordLabel.Location = new System.Drawing.Point(30, 435);
            this.displayWordLabel.Name = "displayWordLabel";
            this.displayWordLabel.Size = new System.Drawing.Size(111, 44);
            this.displayWordLabel.TabIndex = 6;
            this.displayWordLabel.Text = "Word";
            // 
            // usedLettersLabel
            // 
            this.usedLettersLabel.AutoSize = true;
            this.usedLettersLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F);
            this.usedLettersLabel.Location = new System.Drawing.Point(830, 30);
            this.usedLettersLabel.Name = "usedLettersLabel";
            this.usedLettersLabel.Size = new System.Drawing.Size(177, 31);
            this.usedLettersLabel.TabIndex = 7;
            this.usedLettersLabel.Text = "Used Letters:";
            // 
            // HangMan
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.usedLettersLabel);
            this.Controls.Add(this.displayWordLabel);
            this.Controls.Add(this.drawingArea);
            this.Controls.Add(this.restartButton);
            this.Controls.Add(this.guessButton);
            this.Controls.Add(this.insertLetterBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "HangMan";
            this.Text = "HangMan";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            ((System.ComponentModel.ISupportInitialize)(this.drawingArea)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.RichTextBox insertLetterBox;
        private System.Windows.Forms.Button guessButton;
        private System.Windows.Forms.Button restartButton;
        private System.Windows.Forms.PictureBox drawingArea;
        private System.Windows.Forms.Label displayWordLabel;
        private System.Windows.Forms.Label usedLettersLabel;
    }
}

