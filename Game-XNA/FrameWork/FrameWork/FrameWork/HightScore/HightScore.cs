using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace FrameWork.FrameWork.HightScore
{
    class Score
    {
        static Score m_Instance;

        List<int> m_Score;

        public List<int> HightScore
        {
            get { return m_Score; }
            set { m_Score = value; }
        }

        protected Score()
        {
            m_Score = new List<int>();
        }

        public static Score Instance()
        {
            if (m_Instance == null)
            {
                m_Instance = new Score();
            }
            return m_Instance;
        }
        static int Comparison(int _x, int _y)
        {
            return _x > _y ? -1 : 1;
        }
        public int AddScore (int _Score)
        {
            m_Score.Add(_Score);
            m_Score.Sort(Comparison);

            for (int i = 0; i < m_Score.Count; i++ )
            {
                if (m_Score[i]== _Score)
                {
                    return (i + 1);
                }                
            }
            return 0;
        }

        public void LoadScore(string _path)
        {
            TextReader tr = new StreamReader(_path);
            int count =Convert.ToInt32(tr.ReadLine());
            for (int i = 0; i < count;i++ )
            {
                AddScore(Convert.ToInt32(tr.ReadLine()));
            }           
            tr.Close();
        }
        public void SaveScore(string _path)
        {           
            TextWriter tw = new StreamWriter(_path);
            tw.WriteLine(m_Score.Count);

            for (int i = 0; i < m_Score.Count; i++ )
            {
                tw.WriteLine(m_Score[i].ToString());
            }              
            tw.Close();
        }
       
    }
}
