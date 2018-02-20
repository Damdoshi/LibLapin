<div class="prototype">
  XML format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The XML format is a partially recursive format: most nodes contains
    hashmap and arrays but only array can contain nodes.
    <br />
    The general appeirence of XML is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo xml_file(dirname(__FILE__)."/251_xml_file.xml"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    conf_node.named_children = $L"data"@<br />
    conf_node[0] = $L"ArrayInput"@<br />
    conf_node[1].named_children[0] = $L"data"@<br />
    conf_node[1].named_children[1] = $L"second_data"@<br />
    conf_node[2] = $L"extensions"@<br />
    conf_node[2].named_children = $L"data"@<br />
    conf_node[2][0] = $L"Data"@<br />
    <br />
    Note that array_input2 and array_input3 are indexed nodes even if they
    have a name. This is because what is looking like a XML field name is
    not a field name but the markup type, so it can be used several time inside
    the same array. This name is <b>still registered</b> and will be returned
    as the node name if requested, and regenerated if the configuration is saved.
    <br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br >
    <br />
    XML commentaries are block only, start with '&lt;!--' and end with '--&gt;'.<br />
    <br />
    An XML file is supposed to have a doctype, but the bunny configuration does not
    support it. Also, an XML file is supposed to have a single root markup written,
    but the bunny configuration XML does not require it.<br />
    <br />
    The markup value is a bunny configuration extensions.<br />
    <br />
    The markup property as array is a bunny configuration extension.<br />
    <br />
  </p>
  <br />
  <br />
</div>
