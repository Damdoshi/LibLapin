<div class="prototype">
  CSV format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The CSV format represents 2D matrices. The bunny configuration version
    of CSV use ';' as row separator and new line '\n' as line separator.
    <br />
    The general appeirence of CSV is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo csv_file(dirname(__FILE__)."/401_csv_format.csv"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    [0][0] = "name"<br />
    [0][1] = "game"<br />
    [0][2] = "date"<br />
    [1][0] = "roger"<br />
    [1][1] = "space quest"<br />
    [1][2] = 1985<br />
    [2][0] = "link"<br />
    [2][1] = "zelda"<br />
    [2][2] = 1985<br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br >
    <br />
  </p>
  <br />
  <br />
</div>
