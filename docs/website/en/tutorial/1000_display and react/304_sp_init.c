  main_data.pic = bunny_load_picture("./sprite.png");
  main_data.pic->clip_width = 107;
  main_data.pic->clip_height = 100;
  main_data.pic->origin.x = main_data.pic->clip_width / 2;
  main_data.pic->origin.y = main_data.pic->clip_height / 2;
  main_data.pic->position.x = main_data.win->buffer.width / 2;
  main_data.pic->position.y = main_data.win->buffer.height / 2;

  main_data.animation_frame = 0;
