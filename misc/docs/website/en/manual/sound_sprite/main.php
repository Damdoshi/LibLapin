<p>
  The sound sprite module helps you to save memory when you have a lot
  of short sound files (like dialogues in a video game): compile them
  into a single sound file and write an according configuration file
  and the system will see how to split it and play those sounds as if
  they were separated.
</p>
<p>
  If you set a sound manager, pay attention: the sound sprite play and
  stop functions must be called instead of the sound manager play and
  stop functions (they are called anyway by sound sprite play and stop)
</p>

