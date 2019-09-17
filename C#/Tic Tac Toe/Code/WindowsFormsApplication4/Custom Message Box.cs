using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication4
{
    public partial class Custom_Message_Box : Form
    {
        public Custom_Message_Box()
        {
            InitializeComponent();
        }

        private void Custom_Message_Box_Load(object sender, EventArgs e)
        {

        }
        static Custom_Message_Box MsgBox; static DialogResult result = DialogResult.No;
        public static DialogResult Show(string Text, string Caption, string sadButton)
        {
            MsgBox = new Custom_Message_Box();
            MsgBox.label1.Text = Text;
            MsgBox.button1.Text =  sadButton;
            MsgBox.Text = Caption;
            MsgBox.ShowDialog();
            return result;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            result = DialogResult.Yes; MsgBox.Close();
        }
    }
}
