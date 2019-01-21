using System;
using System.Collections.Generic;
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
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            
        }
        /// <summary>
        /// 按行读取文本文件内容，返回一个ArrayList，每一个元素是一行内容
        /// </summary>
        /// <param name="file_path"></param>
        /// <returns></returns>
      
    }

    
        public static class DrawTool
        {
            /// <summary>
            /// 线画笔颜色，在构造函数中初始化何种颜色
            /// </summary>
            public static Color line_brush_color = new Color();
            /// <summary>
            /// 圈画笔颜色，在构造函数中初始化何种颜色
            /// </summary>
            public static Color circle_brush_color = new Color();

            static DrawTool()
            {
                DrawTool.line_brush_color = Color.FromArgb(0, 0, 0);
                DrawTool.circle_brush_color = Color.FromArgb(0, 0, 255);
            }

            /// <summary>
            /// 绘制指定颜色粗细带箭头的线
            /// </summary>
            public static void DrawArrowLine(Graphics g, float x1, float y1, float x2, float y2, float width)
            {
                Pen p = new Pen(DrawTool.line_brush_color, width);
                p.EndCap = LineCap.ArrowAnchor;  // 定义线尾的样式为箭头
                g.DrawLine(p, x1, y1, x2, y2);
            }

            /// <summary>
            /// 绘制圆心(x,y),半径r,宽度为width的空心圆
            /// </summary>
            public static void DrawCircle(Graphics g, float x, float y, float r, float width)
            {
                Pen p = new Pen(DrawTool.circle_brush_color, width);
                g.DrawEllipse(p, (int)(x - r), (int)(y - r), (int)(2 * r), (int)(2 * r));
            }
        }

    }