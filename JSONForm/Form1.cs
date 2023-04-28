using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace JSONForm
{
    public partial class Form1 : Form
    {
        static JSONLib.JSONNet js = new JSONLib.JSONNet();
        public Form1()
        {
            InitializeComponent();
        }

        public class ShowJSON : JSONLib.IObserver
        {
            public void show()
            {
                label.Text = js.getJsonString();
            }
            Label label;
            JSONLib.JSONNet js;
            public ShowJSON(Label l, JSONLib.JSONNet js)
            {
                this.js = js;
                label = l;
            }
            override public void Refresh()
            {
                show();
            }

        };

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            JSONLib.ValueNet val1 = new JSONLib.ValueNet("firstName", "Lazzaro");
            JSONLib.ValueNet val2 = new JSONLib.ValueNet("lastName", "Raimondi");
            JSONLib.ListValueNet val3 = new JSONLib.ListValueNet("address", "");
            JSONLib.ValueNet val31 = new JSONLib.ValueNet("city", "Milan");
            JSONLib.ValueNet val32 = new JSONLib.ValueNet("street", "San-Siro");
            JSONLib.ValueNet val4 = new JSONLib.ValueNet("job", "manager");
            val3.addFirst(val32);
            val3.addFirst(val31);
            js.addFirst(val4);
            js.addFirst(val3);
            js.addFirst(val2);
            js.addFirst(val1);
            ShowJSON sl = new ShowJSON(label1, js);
            sl.show();
            js.SetObserver(sl);
        }

        private void label1_Click(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string key = textBox1.Text;
            string value = textBox2.Text;
            if ((key != "") && (value != ""))
            {
                try
                {
                    JSONLib.ValueNet newvalue = new JSONLib.ValueNet(key, value);
                    js.addFirst(newvalue);
                }
                catch (FormatException ee)
                {

                }
            }
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            js.next();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            js.down();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            js.back();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string key = textBox1.Text;
            string value = textBox2.Text;
            if ((key != "") && (value != ""))
            {
                try
                {
                    JSONLib.ValueNet newvalue = new JSONLib.ValueNet(key, value);
                    js.add(newvalue);
                }
                catch (FormatException ee)
                {

                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            js.deleteFirst();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            js.del();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            js.up();
        }
    }
}
