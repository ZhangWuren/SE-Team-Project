using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using test_subway1;

namespace test_subway1
{
    public partial class Form1 : Form
    {
        public static Graphics graphics = null;

        public Form1()
        {
            InitializeComponent();
            Form1.graphics = pictureBox1.CreateGraphics();
            this.Show();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
        private void From1_MouseClick(object sender, MouseEventArgs e)
        {

           
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            ResetMap();
            StreamReader sr = new StreamReader("zcl_subway_station.txt", Encoding.Default);
            String readline;
            float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
            int flag_first = 0;
            int index = 0;
            while ((readline = sr.ReadLine()) != null)
            {
                x2 = 0;
                y2 = 0;
                index = 0;
                while (readline[index] != ' ')
                {
                    x2 = x2 * 10 + readline[index] - '0';
                    index++;
                }
                index++;
                while (index < readline.Length)
                {
                    y2 = y2 * 10 + readline[index] - '0';
                    index++;
                }
                DrawTool.DrawCircle(graphics, x2, y2, 8,2);
                if (flag_first == 0) flag_first = 1;
                else
                {//画从x1，y1到x2，y2的线
                    DrawTool.DrawArrowLine(graphics, x1, y1, x2, y2, 2);
                }
                x1 = x2;
                y1 = y2;

            }
           }
  

        public void ResetMap()
        {
            Bitmap bitmap = new Bitmap("subway_map.bmp");
            Rectangle r = new Rectangle(0, 0,this.pictureBox1.Size.Width, this.pictureBox1.Size.Height);
            Form1.graphics.DrawImage(bitmap, r);  // 使用原地图覆盖
        }
    }
}
