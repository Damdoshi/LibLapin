<p>
  This module brings ciphering ability to the LibLapin.<br />

  <b>Please</b>, read those lines carefuly: this module is <b>NOT</b>
  designed as a really secure module. Its only purpose is to cipher
  and uncipher ressources used by your program to prevent things
  like cheating. Eventually, it could be used as additional security
  in a really secure channel, but remember: if you need real
  security, use a real ciphering library.
</p>

<p>
  A note about ciphering and unciphering functions: you should
  consider ciphering as an operation in a specific direction and
  unciphering as the opposed direction, but specificaly as ciphering
  and unciphering operations.
  With algorithm offered
  by the bunny library, you can without any problem
  cipher with and unciphering function and uncipher with a ciphering
  function.<br />
  All you have to do is keep the consistancy of your actions. If you have
  ciphered with an unciphering function with an algorithm, then
  you have to uncipher with a ciphering function with the same algorithm
  to get your data back.
</p>

<b>The security module header is lapin/security.h.</b>
