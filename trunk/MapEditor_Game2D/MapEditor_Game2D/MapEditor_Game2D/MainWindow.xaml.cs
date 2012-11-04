using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Windows.Controls.Ribbon;
using System.Drawing;

namespace MapEditor_Game2D
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {
        public int m_WidthMap;
        public int m_HieghtMap;
        public CImage[,] m_MapTitle;
        public int m_IndexSelect;
        public int m_TimeMap;
        public MainWindow()
        {
            InitializeComponent();
            m_IndexSelect = 1;
            m_HieghtMap = 0;
            m_WidthMap = 0;
            m_MapTitle = null;
            m_TimeMap = 100;// 10 phut
            // Insert code required on object creation below this point.
        }

        public void CreateMap(int _Width,int _Height)
        {
            m_WidthMap = _Width;
            m_HieghtMap = _Height;
            Mouse.OverrideCursor = Cursors.Wait;            
            Map_panel.Children.Clear();

            Map_panel.Width = 25 * (1 + _Width);
            Map_panel.Height = 25 * (1 + _Height);

            m_MapTitle = new CImage[_Width,_Height];

            for (int i = 0; i < _Width + 1;i++ )
            {

                TextBlock Num = new TextBlock();
                Num.Background = new SolidColorBrush(Colors.LightGray);
                Num.Text = (i - 1).ToString();
                if (i == 0)
                {
                    Num.Text = " ";
                }
                Num.Height = 25;
                Num.Width = 25;
                Num.TextAlignment = TextAlignment.Center;
                Map_panel.Children.Add(Num);
            }

            for (int j = 0; j < _Height; j++)
            {
                TextBlock Num = new TextBlock();
                Num.Background = new SolidColorBrush(Colors.LightGray);
                Num.Height = 25;
                Num.Width = 25;
                Num.Text = j.ToString();
                Num.TextAlignment = TextAlignment.Center;
                Map_panel.Children.Add(Num);
                for (int i = 0; i < _Width; i++)
                {
                    m_MapTitle[i, j] = new CImage();
                    m_MapTitle[i, j].Index = 0;
                    m_MapTitle[i, j].MouseLeftButtonDown += EditorMap;
                    m_MapTitle[i, j].MouseRightButtonDown += DeleteEditorMap;
                    m_MapTitle[i, j].Margin = new Thickness(0, 0, 0, 0);
                    m_MapTitle[i, j].Height = 25;
                    m_MapTitle[i, j].Width = 25;
                    m_MapTitle[i, j].ToolTip = "[" + i.ToString() + "," + j.ToString() + "]";
                    Map_panel.Children.Add(m_MapTitle[i, j]);
                }
            }

            Mouse.OverrideCursor = null;
        }
        private void EditorMap(object sender, MouseButtonEventArgs e)
        {
            CImage fe1 = (CImage)e.Source;
            fe1.Index = m_IndexSelect;
        }
        private void DeleteEditorMap(object sender, MouseButtonEventArgs e)
        {
            CImage fe1 = (CImage)e.Source;
            fe1.Index = 0;
        }
        private void setIndexselect(int _Index)
        {
            m_IndexSelect = _Index;
            string path = "pack://application:,,,/Images/" + _Index.ToString() + ".png";
            select_Image.Source = new BitmapImage(new Uri(path));
        }
        private void New_bt_Click(object sender, RoutedEventArgs e)
        {
            New n = new New();
            n.ShowDialog();
            if (n.iOK)
            {
                try
                {
                    int w = Convert.ToInt32(n.Width_tb.Text);
                    int h = Convert.ToInt32(n.Height_tb.Text);
                    m_TimeMap = Convert.ToInt32(n.Time_tb.Text);
                    CreateMap(w, h);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
            
        }

        private void Open_bt_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.FileName = "Map"; // Default file name
            dlg.DefaultExt = ".png"; // Default file extension
            dlg.Filter = " (.png)|*.png"; // Filter files by extension
            // Show open file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results
            if (result == true)
            {
                string filename = dlg.FileName;
                Bitmap map = new Bitmap(filename);
                System.Drawing.Color pixel = map.GetPixel(0, 0);
                m_TimeMap = pixel.A;
                CreateMap(map.Width, map.Height);
                for (int i = 0; i < map.Width; i++)
                {
                    for (int j = 0; j < map.Height; j++)
                    {
                        System.Drawing.Color pixelColor = map.GetPixel(i, j);
                        m_MapTitle[i, j].Index = pixelColor.R;
                    }
                }
                
            }
        }
        private void Edit_bt_Click(object sender, RoutedEventArgs e)
        {
            New n = new New();
            n.Width_tb.Text = m_WidthMap.ToString();
            n.Height_tb.Text = m_HieghtMap.ToString();
            n.Time_tb.Text = m_TimeMap.ToString();
            n.ShowDialog();
            if (n.iOK)
            {
                try
                {
                    Mouse.OverrideCursor = Cursors.Wait;
                    m_TimeMap = Convert.ToInt32(n.Time_tb.Text);
                    int w = Convert.ToInt32(n.Width_tb.Text);
                    int h = Convert.ToInt32(n.Height_tb.Text);
                    if (w != m_WidthMap || h != m_HieghtMap)
                    {
                        // Copy du lieu map cu vao bo nho tam
                        int[,] mapOld = new int[m_WidthMap, m_HieghtMap];

                        for (int i = 0; i < m_WidthMap; i++)
                        {
                            for (int j = 0; j < m_HieghtMap; j++)
                            {
                                mapOld[i,j] = m_MapTitle[i, j].Index;
                            }
                        }
                        int wOld = m_WidthMap;
                        int hOld = m_HieghtMap;
                        // Tao map moi
                        CreateMap(w, h);
                        int mW = Math.Min(wOld, w);
                        int mH = Math.Min(hOld, h);

                        for (int i = 0; i < mW; i++)
                        {
                            for (int j = 0; j < mH; j++)
                            {
                                m_MapTitle[i, j].Index = mapOld[i, j];
                            }
                        }
                    }
                    
                    
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }                
                finally
                {
                    Mouse.OverrideCursor = null;
                }
            }
        }
        private void Save_bt_Click(object sender, RoutedEventArgs e)
        {
            if (m_MapTitle!= null)
            {
                Mouse.OverrideCursor = Cursors.Wait;
                Bitmap map = new Bitmap(m_WidthMap, m_HieghtMap);
                for (int i = 0; i < map.Width; i++)
                {
                    for (int j = 0; j < map.Height; j++)
                    {
                        map.SetPixel(i, j, System.Drawing.Color.FromArgb(m_TimeMap,m_MapTitle[i,j].Index,0,0));
                    }
                }
                Mouse.OverrideCursor = null;
                try
                {
                    // Configure save file dialog box
                    Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
                    dlg.FileName = "1"; // Default file name
                    dlg.DefaultExt = ".png"; // Default file extension
                    dlg.Filter = " (.png)|*.png"; // Filter files by extension

                    // Show save file dialog box
                    Nullable<bool> result = dlg.ShowDialog();

                    // Process save file dialog box results
                    if (result == true)
                    {
                        // Save document
                        string filename = dlg.FileName;
                        map.Save(filename, System.Drawing.Imaging.ImageFormat.Png);
                    }

                   
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            } 
            else
            {
                MessageBox.Show("New or Open map before Save");
            }
           
            
        }

        private void Exit_bt_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void i1_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(1);
        }

        private void i2_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(2);
        }

        private void i3_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(3);
        }

        private void i200_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(200);
        }

        private void i201_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(201);
        }

        private void i202_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(202);
        }

        private void i203_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(203);
        }

        private void i204_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(204);
        }

        private void i205_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(205);
        }

        private void i206_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(206);
        }

        private void i207_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(207);
        }

        private void i208_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(208);
        }

        private void i209_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(209);
        }

        private void i210_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(210);
        }

        private void i211_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(211);
        }

        private void i212_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(212);
        }

        private void i213_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(213);
        }

        private void i214_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(214);
        }

        private void i10_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(10);
        }

        private void i220_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(220);
        }

        private void i221_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(221);
        }

        private void i222_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(222);
        }

        private void i223_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(223);
        }

        private void i224_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(224);
        }

        private void i225_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(225);
        }

        private void i226_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(226);
        }

        private void i227_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(227);
        }

        private void i228_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(228);
        }

        private void i229_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(229);
        }

        private void i230_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(230);
        }

        private void i231_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(231);
        }

        private void i232_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(232);
        }

        private void i233_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(233);
        }

        private void i234_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(234);
        }

        private void i11_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(11);
        }

        private void i12_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(12);
        }

        private void i4_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(4);
        }

        private void i13_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(13);
        }

        private void i14_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(14);
        }

        private void i15_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(15);
        }

        private void i16_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(16);
        }

        private void i17_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(17);
        }

        private void i100_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(100);
        }

        private void i101_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(101);
        }

        private void i102_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(102);
        }

        private void i103_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(103);
        }

        private void i104_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(104);
        }

        private void i105_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(105);
        }

        private void i106_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(106);
        }

        private void i107_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(107);
        }

        private void i108_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(108);
        }

        private void i109_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(109);
        }

        private void i110_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(110);
        }

        private void i111_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(111);
        }

        private void i112_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(112);
        }

        private void i113_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(113);
        }

        private void i114_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(114);
        }

        private void i115_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(115);
        }

        private void i116_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(116);
        }

        private void i117_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(117);
        }

        private void i118_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(118);
        }

        private void i119_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(119);
        }

        private void i120_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(120);
        }

        private void i121_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(121);
        }

        private void i122_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(122);
        }

        private void i123_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(123);
        }

        private void i124_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(124);
        }

        private void i125_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(125);
        }

        private void i126_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(126);
        }

        private void i127_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(127);
        }

        private void i128_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(128);
        }

        private void i129_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(129);
        }

        private void i130_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(130);
        }

        private void i131_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(131);
        }

        private void i90_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(90);
        }

        private void i91_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(91);
        }

        private void i92_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(92);
        }

        private void i93_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(93);
        }

        private void i94_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(94);
        }

        private void i95_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(95);
        }

        private void i96_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(96);
        }

        private void i97_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(97);
        }

        private void i98_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(98);
        }

        private void i99_Click(object sender, RoutedEventArgs e)
        {
            setIndexselect(99);
        }
            
    }
    public class CImage :System.Windows.Controls.Image
    {
        private int m_Index;
        public int Index
        {
            get { return m_Index; }
            set
            {
                m_Index = value;

                string path = "pack://application:,,,/Images/"+m_Index.ToString()+".png";
                this.Source = new BitmapImage(new Uri(path));//BitmapFrame.Create(new Uri(path, UriKind.Relative));
            }
        }    
        
    }
}
