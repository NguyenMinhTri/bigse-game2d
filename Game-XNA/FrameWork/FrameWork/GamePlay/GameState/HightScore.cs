using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

using FrameWork.FrameWork.QuadTree;
using FrameWork.FrameWork.iPlay;
using FrameWork.FrameWork.Graphics;
using FrameWork.FrameWork.Object;
using FrameWork.FrameWork.Audio;
using FrameWork.FrameWork.HightScore;
using FrameWork;

namespace FrameWork.GamePlay.GameState
{
    class HightScore : iState
    {
        List<int> m_Score;

        SpriteFont m_Font;
        Rectangle m_RectButton, m_RectCursor;
        Sprite m_Back, m_Dialog, m_Button, m_Cursor;
        bool m_iTouchButton;
        MouseState old_mouseState, mouseState;

     

        public HightScore(iPlay _iPlay, Game game)
         : base(_iPlay, game)
        {
            ID = STATEGAME.HIGHTSCORE;
        }
        public override void Init()
        {
            m_Score = Score.Instance().HightScore;
            Audio.Instance().StopAllBack();
            Audio.Instance().Play("b_option_state");

            m_Back = RSMainMenu.Instance(Game).SPRITE(3);
            m_Dialog = RSMainMenu.Instance(Game).SPRITE(4);
            m_Dialog.Color = new Color(1, 1, 1, 1.0f);

            m_Button = RSMainMenu.Instance(Game).SPRITE(6);
            m_Cursor = RSMainMenu.Instance(Game).SPRITE(8);

            m_RectButton = new Rectangle(450, 520, 161, 40);
            m_RectCursor = new Rectangle(Mouse.GetState().X, Mouse.GetState().Y, 50, 50);

            m_iTouchButton = false;

            m_Dialog.Position = new Vector2(200, 100);
            m_Button.Position = new Vector2(m_RectButton.X, m_RectButton.Y);
            m_Cursor.Position = new Vector2(m_RectCursor.X, m_RectCursor.Y);

            m_Font = Game.Content.Load<SpriteFont>("SpriteFont2");
        }
        public override void Update(GameTime gameTime)
        {
            mouseState = Mouse.GetState();

            m_RectCursor = new Rectangle(mouseState.X, mouseState.Y, 50, 50);

            #region Update Button
            if (m_RectButton.Intersects(m_RectCursor))
            {
                if (!m_iTouchButton)
                {
                    Audio.Instance().Play("e_chose");
                }
                if (mouseState.LeftButton == ButtonState.Pressed
                    && old_mouseState.LeftButton == ButtonState.Released)
                {
                    Audio.Instance().Play("e_click");
                   
                    this.Play.NextState = new MainMenu(Play, Game);
                }
                m_iTouchButton = true;
            }
            else m_iTouchButton = false;
            #endregion

            old_mouseState = mouseState;
        }
        public override void Render(GameTime gameTime, SpriteBatch _SpriteBatch)
        {
            Game.GraphicsDevice.Clear(Color.Blue);
            _SpriteBatch.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);

            #region Back ground
            m_Back.Render(_SpriteBatch);
            #endregion

            #region Dialog
            m_Dialog.Render(_SpriteBatch);
            #endregion

            #region Render Button
            if (m_iTouchButton)
            {
                m_Button.CurFrame = 1;
            }
            else
            {
                m_Button.CurFrame = 0;
            }
            m_Button.Render(_SpriteBatch);
            #endregion

            _SpriteBatch.DrawString(m_Font, "Main Menu", new Vector2(470, 525), Color.Yellow);

            _SpriteBatch.DrawString(m_Font, "Hight Score", new Vector2(450, 250), 
                Color.Yellow,0,Vector2.Zero,2.0f,SpriteEffects.None,1.0f);

            for (int i = 0;i< m_Score.Count && i<8;i++ )
            {   
                if (i<3)
                {
                    Random r = new Random();
                    int R = r.Next(256);
                    int B = r.Next(256);
                    int G = r.Next(256);
                    _SpriteBatch.DrawString(m_Font, (i + 1).ToString() + ":   " + m_Score[i].ToString(),
                        new Vector2(500, i * 25 + 300), new Color(R,B,G));
                }
                else
                {
                    _SpriteBatch.DrawString(m_Font, (i + 1).ToString() + ":   " + m_Score[i].ToString(),
                        new Vector2(500, i * 25 + 300), Color.Yellow);
                }
                
            }

            m_Cursor.Position = new Vector2(m_RectCursor.X, m_RectCursor.Y);
            m_Cursor.Render(_SpriteBatch);

            _SpriteBatch.End();   
        }
        public override void Destroy()
        {
            
        }
                
    }
   
}
