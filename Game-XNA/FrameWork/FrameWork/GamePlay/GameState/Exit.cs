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

namespace FrameWork.GamePlay.GameState
{
    class Exit : iState
    {
          public Exit(iPlay _iPlay, Game game)
            : base(_iPlay, game)
        {            
            ID = STATEGAME.EXIT;
        }
          public override void Init()
          {
              Score.Instance().SaveScore("Content/Data/Score.txt");
          }
          public override void Update(GameTime gameTime)
          {
              Game.Exit();
          }
    }
}
