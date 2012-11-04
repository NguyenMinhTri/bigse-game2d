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
using System.Windows.Shapes;

namespace MapEditor_Game2D
{
    /// <summary>
    /// Interaction logic for New.xaml
    /// </summary>
    public partial class New : Window
    {
        public New()
        {
            InitializeComponent();
        }
        public bool iOK
        {
            set;
            get;
        }
        private void Width_tb_LostFocus(object sender, RoutedEventArgs e)
        {
            try
            {
                int t = Convert.ToInt32(Width_tb.Text);
                if (t<=0)
                {
                    MessageBox.Show("Error");
                    Width_tb.Text = "0";
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Error");
                Width_tb.Text = "0";
            }
        }

        private void Height_tb_LostFocus(object sender, RoutedEventArgs e)
        {
            try
            {
                int t = Convert.ToInt32(Height_tb.Text);
                if (t <= 0)
                {
                    MessageBox.Show("Error");
                    Height_tb.Text = "0";
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Error");
                Height_tb.Text = "0";
            }
        }

        private void Time_tb_LostFocus(object sender, RoutedEventArgs e)
        {
            try
            {
                int t = Convert.ToInt32(Time_tb.Text);
                if (t <= 0 || t>255)
                {
                    MessageBox.Show("Error");
                    Time_tb.Text = "0";
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Error");
                Time_tb.Text = "0";
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            iOK = true;
            this.Close();

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            iOK = false;
            this.Close();
        }
    }
}
